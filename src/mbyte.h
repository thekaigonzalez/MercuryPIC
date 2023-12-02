// $Id: mbyte.h

#ifndef _MBYTE_H
#define _MBYTE_H

#include "mpool.h"
#include "mvar.h"

typedef struct MByteList MByteList;

MByteList *MByteListNew (MMemoryPool *pool);
void MByteListClear (MByteList *list);
void MByteListAdd (MByteList *list, byte b);
byte *MByteListCopy (MByteList *list);
int MByteListGetSize (MByteList *list);
byte MByteListGet (MByteList *list, int position);

#endif /* _MBYTE_H */
