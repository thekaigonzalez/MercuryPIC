// $Id: msys.h

#ifndef _MSYS_H
#define _MSYS_H

/*defines syscalls*/
/*or basically C functions that perform specific actions then return the
 * results to the caller register */

#include "mbyte.h"
#include "mpool.h"

typedef struct
{
  byte id;
  int (*function) ();
} MSysCall;

MSysCall *MSysCallCreate (MMemoryPool *pool, byte id, int (*function) ());
byte MSysCallRetId (MSysCall *call);
int (*MSysCallRetFunction (MSysCall *call)) ();

#endif
