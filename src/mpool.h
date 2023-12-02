// $Id: mpool.h

#ifndef _MPOOL_H
#define _MPOOL_H

// Include files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* memory pools hold lists to pointers to allocated memory, freeing at runtime
 */
typedef struct MMemoryPool MMemoryPool;

MMemoryPool *MPoolCreate ();
/*note: memset sets all bytes in the array to 0*/
void *MPoolAlloc (MMemoryPool *pool, int size);
/*note: reallocate adds to the array*/
void *MPoolRealloc (MMemoryPool *pool, void *ptr, int size);
void MPoolDestroy (MMemoryPool *pool);

#endif /* _MPool_H */
