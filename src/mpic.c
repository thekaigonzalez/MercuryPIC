#include "mpic.h"
#include "mrt.h"
#include "mrunl.h"

#include <argw.h>

int
pic_main (int argc, char **argv)
{
  argw_init ();

  wFlag *no_runtime
      = argw_flag ('d', "disable-runtime",
                   "Disables the MercuryPIC instruction set.", WBoolean);
  argw_default ('d', false);

  argw_parse (argc, argv);

  if (wArgParserHelpWanted (parser))
    {
      argw_usage ("[options...] filename");
      argw_exit(0);
    }

  char *filename = argw_positional (0);

  if (!filename)
    {
      printf ("mpic: fatal: no input file specified\n");
      printf ("type `mpic -h' for help\n");

    argw_exit(1);
    }

  if (wArgParserStragglyCount (parser) > 1)
    {
      printf ("mpic: fatal: more than one input file specified\n");
      printf ("type `mpic -h' for help\n");
      argw_exit(1);
    }

  // end of argw
  FILE *f = fopen (filename, "r");

  if (!f)
    {
      printf ("mpic: fatal: could not open `%s'\n", filename);
      argw_exit(1);
    }

  MCpu cpu;
  MCpuInitialize (&cpu);

  if (!wValueBoolean (wFlagValue (no_runtime)))
    MRTAddRuntime (&cpu);

  MByteList *list = MByteListNew (cpu.blk);

  char c;
  while ((c = fgetc (f)) != EOF)
    {
      MByteListAdd (list, c);
    }

  fclose (f);

  MRunByteList (&cpu, list);

  MCpuDestroy (&cpu);

  argw_exit(0);
}

int
main (int argc, char **argv)
{
  return pic_main (argc, argv);
}
