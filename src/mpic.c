#include "mpic.h"
#include "mrt.h"
#include "mrunl.h"

#include <argw.h>

#include <stdint.h>
#include <stdlib.h>

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
      argw_exit (0);
    }

  if (wArgParserError (parser))
    {
      printf ("mpic: fatal: option not recognized\n");
      argw_exit (1);
    }

  char *filename = argw_positional (0);

  if (!filename)
    {
      printf ("mpic: fatal: no input file specified\n");
      printf ("type `mpic -h' for help\n");

      argw_exit (1);
    }

  if (wArgParserStragglyCount (parser) > 1)
    {
      printf ("mpic: fatal: more than one input file specified\n");
      printf ("type `mpic -h' for help\n");
      argw_exit (1);
    }

  // end of argw
  FILE *file = fopen (filename, "r");

  if (!file)
    {
      fprintf (stderr, "Error opening file\n");
      return 1;
    }

  fseek (file, 0, SEEK_END);

  long file_size = ftell (file);

  fseek (file, 0, SEEK_SET);

  if (file_size % sizeof(byte) != 0)
    {
      fprintf (stderr, "mpic: fatal: invalid file alignment\n");
      fclose (file);
      return 1;
    }

  MMemoryPool *pool = MPoolCreate ();

  MByteList *list = MByteListNew (pool);

  size_t num_integers = file_size / 4;

  byte *buffer = (byte *)malloc (file_size);

  if (!buffer)
    {
      printf ("mpic: fatal: out of memory\n");
      fclose (file);
      argw_exit (1);
    }

  /* read the 4-spaced file */
  fread (buffer, sizeof(byte), num_integers, file);

  for (uint32_t i = 0; i < num_integers; i++)
    {
      MByteListAdd (list, buffer[i]);
    }

  if (!file)
    {
      printf ("mpic: fatal: could not open `%s'\n", filename);
      argw_exit (1);
    }

  MCpu cpu;
  MCpuInitialize (&cpu);

  if (!wValueBoolean (wFlagValue (no_runtime)))
    MRTAddRuntime (&cpu);

  MRunByteList (&cpu, list);

  MCpuDestroy (&cpu);
  MPoolDestroy (pool);

  free (buffer);
  fclose (file);

  argw_exit (0);
}

int
main (int argc, char **argv)
{
  return pic_main (argc, argv);
}
