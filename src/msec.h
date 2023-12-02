// $Id: msec.h

#ifndef _MSEC_H
#define _MSEC_H

/*defines sections*/

#include "mvar.h"

typedef struct {
  byte data[MERC_SECTION_BYTE_MAX];
  int position;

  /* sections have no locks/owners*/
} MSection;

void MSectionInitialize (MSection *sec);
void MSectionAppend(MSection* sec, byte* data, int size);

#endif
