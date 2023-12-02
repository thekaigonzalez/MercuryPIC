#include "msec.h"

#include <string.h>

void
MSectionInitialize (MSection *sec)
{
  memset (sec->data, 0, MERC_SECTION_BYTE_MAX);
  sec->position = 0;
}

void
MSectionAppend (MSection *sec, byte *data, int size)
{
  for (int i = 0; i < size; i++)
    {
      sec->data[sec->position] = data[i];
      sec->position++;
    }
}
