#include "mrunl.h"
#include "mdef.h"
#include "msyscalls.h"

int
MCpuGoSub (MCpu *cpu, MContext *ctx)
{
  int label = (int)MContextGet (ctx, 1);

  MByteList *tmp = MByteListNew (cpu->blk);

  MSection *section = &cpu->sections[label];

  if (section)
    {
      for (int i = 0; i < (section->position); i++)
        {
          MByteListAdd (tmp, section->data[i]);
        }

      MRunByteList (cpu, tmp);
    }

  return (0);
}

int
MCpuCompare (MCpu *cpu, MContext *ctx)
{
  int a = (int)MContextGet (ctx, 1);
  int b = (int)MContextGet (ctx, 2);

  int lbl1 = (int)MContextGet (ctx, 3);
  int lbl2 = (int)MContextGet (ctx, 4);

  _Bool result = MRegisterCompare (&cpu->registers[a], &cpu->registers[b]);

  if (result)
    {
      // goto subroutine label 1
      MByteList *tmp = MByteListNew (cpu->blk);

      MSection *section = &cpu->sections[lbl1];

      if (section)
        {
          for (int i = 0; i < (section->position); i++)
            {
              MByteListAdd (tmp, section->data[i]);
            }

          MRunByteList (cpu, tmp);
        }
    }
  else
    {
      // otherwise, goto subroutine label 2
      MByteList *tmp = MByteListNew (cpu->blk);

      MSection *section = &cpu->sections[lbl2];

      if (section)
        {
          for (int i = 0; i < (section->position); i++)
            {
              MByteListAdd (tmp, section->data[i]);
            }

          MRunByteList (cpu, tmp);
        }
    }
  return 0;
}

int
MCpuInterrupt (MCpu *cpu, MContext *ctx)
{
  // calls syscall
  MSysCallFind (cpu, MContextGet (ctx, 2))
      ->function (&cpu->registers[(int)MContextGet (ctx, 1)], cpu);

  return 0;
}

byte
MRunByteList (MCpu *cpu, MByteList *list)
{ /*execute bytecode*/
  MByteList *tmp = MByteListNew (cpu->blk);

  int shift = 0; /* how many bytes we've already read */

  /* builtin functions */
  if (!MCpuGetByteOpFunction (cpu, GOSUB) && !MCpuGetByteOpFunction (cpu, CMP)
      && !MCpuGetByteOpFunction (cpu, INT))
    {
      MCpuAddByteOp (cpu, GOSUB, MCpuGoSub);
      MCpuAddByteOp (cpu, CMP, MCpuCompare);
      MCpuAddByteOp (cpu, INT, MCpuInterrupt);
    }

  MAddSyscall (cpu, 0xEE, merc_sys_write);
  MAddSyscall (cpu, 0xEF, merc_sys_shift0);

  _Bool inside_subroutine = false;
  _Bool clean_end = false;
  for (int i = 0; i < MByteListGetSize (list); i++)
    {
      byte current = MByteListGet (list, i);

      if (inside_subroutine == true)
        {
          if (current == ENDSUB)
            {
              inside_subroutine = false;
              shift = 0;
              // TODO: Subroutine code here (...)

              MByteList *body = MByteListNew (cpu->blk);
              for (int j = 1; j < MByteListGetSize (tmp); j++)
                {
                  MByteListAdd (body, MByteListGet (tmp, j));
                }
              byte indx = (int)MByteListGet (tmp, 0);
              if (indx > MERC_SECTION_MAX)
                {
                  fprintf (stderr, "mpic: label out of range: `%d'\n", indx);
                  fprintf (stderr, "mpic: note: max is `%d'\n",
                           MERC_SECTION_MAX);
                  exit (1);
                }
              MSection *lbl = &cpu->sections[indx];

              if (!lbl)
                {
                  fprintf (stderr, "m8: label not found: `%d'\n",
                           MByteListGet (tmp, 0));
                  exit (1);
                }

              MSectionInitialize (lbl);

              if (!MByteListCopy (body))
                {
                  fprintf (stderr, "m8: out of memory\n");
                  exit (1);
                }

              MSectionAppend (lbl, MByteListCopy (body),
                              MByteListGetSize (body));

              MByteListClear (tmp);
            }
          else
            {
              MByteListAdd (tmp, current);
              shift++;
            }
        }
      else if (!inside_subroutine)
        {
          if (current == END && shift == 0)
            {
              clean_end = true;

              break;
            }

          else if (current == SUB && shift == 0 && !inside_subroutine)
            {
              inside_subroutine = true;
              MByteListClear (tmp);
            }

          else if (current == _NULL && shift > 0)
            {
              int (*func) (MCpu *, MContext *)
                  = MCpuGetByteOpFunction (cpu, MByteListGet (tmp, 0));

              if (!func)
                {
                  fprintf (stderr, "m8: instruction not found: `%d'\n",
                           MByteListGet (tmp, 0));
                  exit (1);
                }

              MContext *ctx = MContextNew (cpu->blk, tmp);

              if (func (cpu, ctx))
                {
                  fprintf (stderr, "m8: instruction failed\n");
                  exit (1);
                }

              shift = 0;
              MByteListClear (tmp);
            }
          else if (current == _NULL && shift == 0)
            {
              shift = 0;
            }

          else
            {
              MByteListAdd (tmp, current);
              shift++;
            }
        }
    }

  if (inside_subroutine)
    {
      fprintf (stderr, "m8: subroutine not closed\n");
      exit (1);
    }
  if (clean_end == false)
    {
      fprintf (stderr,
               "m8: PIC: no end found, could not have a clean execution.\n");
      MByteListClear (tmp);
      exit (1);
    }

  return 0;
}
