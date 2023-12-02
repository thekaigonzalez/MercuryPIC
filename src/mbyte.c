#include "mbyte.h"

#include <stdlib.h>

struct MByteList
{
  MMemoryPool *pool_inherited;
  byte *list;
  int size;
  int cap;
};

MByteList *
MByteListNew (MMemoryPool *pool)
{
  MByteList *list = MPoolAlloc (pool, sizeof (MByteList));
  list->list = MPoolAlloc (pool, MERC_MEMORY_POOLING_SIZE);
  list->pool_inherited = pool;
  list->size = 0;
  list->cap = MERC_MEMORY_POOLING_SIZE;

  return list;
}

void
MByteListClear (MByteList *list)
{
  if (list)
    {
      memset (list->list, 0, list->cap);
      list->size = 0;
      list->cap = MERC_MEMORY_POOLING_SIZE;
    }
}

void
MByteListAdd (MByteList *list, byte b)
{
  if (list->size >= list->cap)
    {
      list->cap *= 2;
      list->list = MPoolRealloc (list->pool_inherited, list->list, list->cap);
    }

  list->list[list->size] = b;
  list->size++;
}

byte *
MByteListCopy (MByteList *list)
{
  if (list)
    {
      byte *copy = MPoolAlloc (list->pool_inherited, list->size + 1);

      memcpy (copy, list->list, list->size);

      return copy;
    }

  return NULL;
}

int
MByteListGetSize (MByteList *list)
{
  if (list)
    {
      return list->size;
    }
  return 0;
}

byte
MByteListGet (MByteList *list, int position)
{
  if (list && position >= 0 && position < list->size) {
    return list->list[position];
  }

  return -127;
}
