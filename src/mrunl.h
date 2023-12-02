// $Id: mrunl.h

#ifndef _MRUNL_H
#define _MRUNL_H

/*execute bytecode*/

#include "mdef.h"
#include "mcpu.h"
#include "mpool.h"
#include "mctx.h"
#include "mreg.h"
#include "mbyte.h"

byte MRunByteList(MCpu *cpu, MByteList *list);

void MRTAddRuntime(MCpu *cpu);

#endif /* _MRUNL_H */
