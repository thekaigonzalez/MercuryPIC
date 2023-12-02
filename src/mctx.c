#include "mctx.h"

struct MContext
{
  MMemoryPool *pool_inherited;
  byte *listing;
  int size;
};

MContext *
MContextNew (MMemoryPool *pool, MByteList *listing)
{
  MContext *ctx = MPoolAlloc (pool, sizeof (MContext));
  ctx->pool_inherited = pool;
  ctx->listing = MByteListCopy (listing);
  ctx->size = MByteListGetSize (listing);

  return ctx;
}

byte
MContextGet (MContext *ctx, int position)
{
  if (ctx && position >= 0 && position < ctx->size)
    {
      return ctx->listing[position];
    }
  return -127;
}

int
MContextSize (MContext *ctx)
{
  if (ctx)
    {
      return ctx->size;
    }
  return 0;
}
