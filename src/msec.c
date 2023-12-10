#include "msec.h"

#include <stdio.h>
#include <string.h>

void
MSectionInitialize (MSection *sec)
{
  memset (sec->data, 0, MERC_SECTION_BYTE_MAX * sizeof (byte));
  sec->position = 0;
}

void
MSectionAppend (MSection *sec, byte *data, int size)
{
  if (!data || !sec)
    {
      printf ("m8: invalid data\n");
      return;
    }
  for (int i = 0; i < size; i++)
    {
      if (sec->position >= MERC_SECTION_BYTE_MAX)
        {
          printf ("m8: potential section overflow, had to truncate\n");
          return;
        }
      sec->data[sec->position] = data[i];
      sec->position++;
    }
}
