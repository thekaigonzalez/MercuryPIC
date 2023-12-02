#include "msys.h"

MSysCall *
MSysCallCreate (MMemoryPool *pool, byte id, int (*function) ())
{
  MSysCall *call = MPoolAlloc (pool, sizeof (MSysCall));

  call->id = id;
  call->function = function;

  return call;
}

byte
MSysCallRetId (MSysCall *call)
{
  if (call)
    {
      return call->id;
    }
}

int (*MSysCallRetFunction (MSysCall *call)) ()
{
  if (call)
    {
      return call->function;
    }
}
