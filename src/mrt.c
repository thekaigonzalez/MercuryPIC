#include "mrt.h"
#include "mdef.h"

int
mrt_echo (MCpu *cpu, MContext *ctx)
{
  if (MContextSize (ctx) < 2)
    {
      fprintf (stderr, "m8: ECHO instruction: not enough arguments\n");
      return 1;
    }
  byte out = MContextGet (ctx, 1);

  printf ("%c", out);
  return 0;
}

int
mrt_initsection (MCpu *cpu, MContext *ctx)
{
  if (MContextSize (ctx) < 2)
    {
      fprintf (stderr, "m8: INITSECTION instruction: not enough arguments\n");
      return 1;
    }

  int num = (int)MContextGet (ctx, 1);

  if (&cpu->sections[num])
    MSectionInitialize (&cpu->sections[num]);
  else
    {
      fprintf (stderr, "m8: INITSECTION instruction: section not found\n");
      return 1;
    }

  return 0;
}

int
mrt_init (MCpu *cpu, MContext *ctx)
{
  if (MContextSize (ctx) < 2)
    {
      fprintf (stderr, "m8: INIT instruction: not enough arguments\n");
      return 1;
    }

  int num = (int)MContextGet (ctx, 1);

  if (&cpu->registers[num])
    {
      MRegisterInitialize (&cpu->registers[num]);
    }
  else
    {
      fprintf (stderr, "m8: INIT instruction: register not found\n");
      return 1;
    }
  return 0;
}

int
mrt_put (MCpu *cpu, MContext *ctx)
{
  if (MContextSize (ctx) < 4)
    {
      fprintf (stderr, "m8: PUT instruction: not enough arguments\n");
      return 1;
    }

  int reg = (int)MContextGet (ctx, 1);
  byte b = (byte)MContextGet (ctx, 2);
  int pos = (int)MContextGet (ctx, 3);

  if (&cpu->registers[reg])
    {
      cpu->registers[reg].data[pos] = b;
    }
  else
    {
      fprintf (stderr, "m8: PUT instruction: register not found\n");
      return 1;
    }

  return 0;
}

int
mrt_each (MCpu *cpu, MContext *ctx)
{
  if (MContextSize (ctx) < 2)
    {
      fprintf (stderr, "m8: EACH instruction: not enough arguments\n");
      return 1;
    }

  int reg = (int)MContextGet (ctx, 1);

  if (&cpu->registers[reg])
    {
      for (int i = 0; i < MERC_REGISTER_BYTE_MAX; i++)
        {
          if (cpu->registers[reg].data[i])
            {
              if (cpu->registers[reg].data[i] != 0)
                {
                  printf ("%c", cpu->registers[reg].data[i]);
                }
            }
        }
    }
  return 0;
}

int
mrt_get (MCpu *cpu, MContext *ctx)
{
  if (MContextSize (ctx) < 3)
    {
      fprintf (stderr, "m8: GET instruction: not enough arguments\n");
      return 1;
    }

  int reg = (int)MContextGet (ctx, 1);
  int pos = (int)MContextGet (ctx, 2);
  int out = (int)MContextGet (ctx, 3);

  if (&cpu->registers[reg])
    {
      byte b = MRegisterAtPosition (&cpu->registers[reg], pos);
      MRegisterPush (&cpu->registers[out], b);
    }
  return 0;
}

int
mrt_mov (MCpu *cpu, MContext *ctx)
{
  if (MContextSize (ctx) < 3)
    {
      fprintf (stderr, "m8: MOV instruction: not enough arguments\n");
      return 1;
    }

  int reg = (int)MContextGet (ctx, 1);

  MReg *rcpu = &cpu->registers[reg];

  if (rcpu)
    {
      byte b = (byte)MContextGet (ctx, 2);

      MRegisterPush (rcpu, b);
    }
  return 0;
}

int
mrt_lsl (MCpu *cpu, MContext *ctx)
{
  // add bytes to a register in sequence

  if (MContextSize (ctx) < 2)
    {
      fprintf (stderr, "m8: LSL instruction: not enough arguments\n");
      return 1;
    }

  int reg = (int)MContextGet (ctx, 1);

  MReg *rcpu = &cpu->registers[reg];

  if (rcpu)
    {
      for (int i = 2; i < MContextSize (ctx); i++)
        {
          byte b = (byte)MContextGet (ctx, i);

          MRegisterPush (rcpu, b);
        }
    }
  return 0;
}

int
mrt_inc (MCpu *cpu, MContext *ctx)
{
  if (MContextSize (ctx) < 2)
    {
      fprintf (stderr, "m8: INC instruction: not enough arguments\n");
      return 1;
    }

  int reg = (int)MContextGet (ctx, 1);

  MReg *rcpu = &cpu->registers[reg];

  if (rcpu)
    {
      MRegisterIncrement (rcpu);
    }
  return 0;
}

int
mrt_reset (MCpu *cpu, MContext *ctx)
{
  if (MContextSize (ctx) < 2)
    {
      fprintf (stderr, "m8: RESET instruction: not enough arguments\n");

      return 1;
    }

  int reg = (int)MContextGet (ctx, 1);

  MReg *rcpu = &cpu->registers[reg];

  if (rcpu)
    {
      MRegisterInitialize (rcpu);
    }

  return 0;
}

int
mrt_clear (MCpu *cpu, MContext *ctx)
{
  // clear every register

  for (int i = 0; i < MERC_REGISTER_MAX; i++)
    {
      MRegisterInitialize (&cpu->registers[i]);
    }
  return 0;
}

int
mrt_in (MCpu *cpu, MContext *ctx)
{
  if (MContextSize (ctx) < 2)
    {
      fprintf (stderr, "m8: IN instruction: not enough arguments\n");
      return 1;
    }
  // get input from stdin

  int reg = (int)MContextGet (ctx, 1);

  char c = fgetc (stdin);

  MRegisterPush (&cpu->registers[reg], c);
  return 0;
}

int
mrt_add (MCpu *cpu, MContext *ctx)
{
  if (MContextSize (ctx) < 3)
    {
      fprintf (stderr, "m8: ADD instruction: not enough arguments\n");
      return 1;
    }

  int reg = (int)MContextGet (ctx, 1);
  int out = (int)MContextGet (ctx, 2);

  MReg *rcpu = &cpu->registers[reg];

  if (rcpu)
    {
      int result = 0;

      for (int i = 0; i < MERC_REGISTER_BYTE_MAX; i++)
        {
          result += MRegisterAtPosition (rcpu, i);
        }

      MRegisterPush (&cpu->registers[out], (char)result);
    }
  return 0;
}

int
mrt_rcl (MCpu *cpu, MContext *ctx)
{
  // print all contenbts of a register, as a number

  if (MContextSize (ctx) < 3) {
    fprintf (stderr, "m8: RCL instruction: not enough arguments\n");
    return 1;
  }

  int reg = (int)MContextGet (ctx, 1);
  int at = (int)MContextGet (ctx, 2);

  MReg *rcpu = &cpu->registers[reg];

  if (rcpu) {
    printf("%d", MRegisterAtPosition (rcpu, at));
  }
  return 0;
}

void
MRTAddRuntime (MCpu *cpu)
{
  MCpuAddByteOp (cpu, ECHO, mrt_echo);
  MCpuAddByteOp (cpu, MOVE, mrt_mov);
  MCpuAddByteOp (cpu, EACH, mrt_each);

  MCpuAddByteOp (cpu, RESET, mrt_reset);
  MCpuAddByteOp (cpu, CLEAR, mrt_clear);

  MCpuAddByteOp (cpu, PUT, mrt_put);
  MCpuAddByteOp (cpu, GET, mrt_get);

  MCpuAddByteOp (cpu, ADD, mrt_add);

  MCpuAddByteOp (cpu, LSL, mrt_lsl);
  MCpuAddByteOp (cpu, IN, mrt_in);

  MCpuAddByteOp (cpu, INC, mrt_inc);
  MCpuAddByteOp (cpu, RCL, mrt_rcl);

  MCpuAddByteOp (cpu, INITSEC, mrt_initsection);
  MCpuAddByteOp (cpu, INIT, mrt_init);
}
