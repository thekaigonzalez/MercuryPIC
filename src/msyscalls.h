// $Id: msyscalls.h

#ifndef _MSYSCALLS_H
#define _MSYSCALLS_H

/*implements syscalls*/
#include "mbyte.h"
#include "mpool.h"
#include "mreg.h"
#include "mcpu.h"

int merc_sys_write(MReg* regist, MCpu* cpu); /*0xEE*/
int merc_sys_shift0(MReg* regist, MCpu* cpu); /*0xEF*/

#endif
