// $Id: mctx.h

#ifndef _MCTX_H
#define _MCTX_H

#include "mreg.h"
#include "mpool.h"
#include "mbyte.h"

typedef struct MContext MContext;

MContext* MContextNew(MMemoryPool *pool, MByteList *listing);
byte MContextGet(MContext *ctx, int position);
int MContextSize(MContext *ctx);

#endif
