#include "mpool.h"
#include "mvar.h"

struct MMemoryPool
{
  void **list;
  int size;
  int capacity;
  int hard_limit;
};

MMemoryPool *
MPoolCreate ()
{
  MMemoryPool *pool = (MMemoryPool *)malloc (sizeof (MMemoryPool));
  if (!pool)
    {
      fprintf (stderr, "MPoolCreate: out of memory for *pool\n");
      return NULL;
    }

  pool->list = (void **)malloc (sizeof (void *) * MERC_MEMORY_POOLING_SIZE);

  if (!pool->list)
    {
      fprintf (stderr, "MPoolCreate: out of memory for *pool->list\n");
      free (pool);
      return NULL;
    }

  pool->size = 0;
  pool->capacity = MERC_MEMORY_POOLING_SIZE;
  pool->hard_limit = MERC_HARDLIMIT;

  return pool;
}

void *
MPoolAlloc (MMemoryPool *pool, int size)
{
  if (!pool || size <= 0) {
    return NULL;
  }
  if (pool->size >= pool->capacity)
    {
      pool->list = (void **)realloc (pool->list,
                                     sizeof (void *) * pool->capacity * 2);
      pool->capacity *= 2;
    }
  void *mem_ptr = malloc (size * sizeof (void *));

  if (!mem_ptr)
    {
      return NULL;
    }

  memset (mem_ptr, 0, size);

  pool->list[pool->size] = mem_ptr;
  pool->size++;

  return mem_ptr;
}

void *
MPoolRealloc (MMemoryPool *pool, void *ptr, int size)
{
  if (!pool || !ptr)
    {
      return NULL;
    }

  void *mem_ptr = realloc (ptr, size);

  if (mem_ptr)
    {
      // add to list
      for (int i = 0; i < pool->size; i++)
        {
          if (pool->list[i] == ptr)
            {
              pool->list[i] = mem_ptr;
            }
        }

      return mem_ptr;
    }

  if (!mem_ptr)
    {
      return NULL;
    }

  return NULL;
}

void
MPoolDestroy (MMemoryPool *pool)
{
  if (!pool)
    {
      return;
    }

  for (int i = 0; i < pool->size; i++)
    {
      if (pool->list[i])
        free (pool->list[i]);
    }

  if (pool->list)
    {
      free (pool->list);
      free (pool);
    }
}
