// $Id: mrt.h

#ifndef _MRT_H
#define _MRT_H

/*runtime functions*/
/*contains instructions for moving data between registers*/

#include "mcpu.h"
#include "mctx.h"
#include "mreg.h"
#include "msec.h"
#include "mvar.h"

int mrt_echo (MCpu *cpu, MContext *ctx);        /* ECHO {byte} */
int mrt_initsection (MCpu *cpu, MContext *ctx); /* INITSECTION {num} */
int mrt_init (MCpu *cpu, MContext *ctx);        /* INIT {num} */
int mrt_put (MCpu *cpu, MContext *ctx);         /* PUT {regnum} {byte} {pos} */
int mrt_each (MCpu *cpu, MContext *ctx);        /* EACH {regnum} */
int mrt_get (MCpu *cpu, MContext *ctx); /* GET {regnum} {pos} {output_reg} */
int mrt_mov (MCpu *cpu, MContext *ctx); /* MOV {reg} {byte} */
int mrt_lsl (MCpu *cpu, MContext *ctx); /* LSL {reg} {bytes ...}*/
int mrt_inc (MCpu *cpu, MContext *ctx); /* INC {reg} */
int mrt_reset(MCpu *cpu, MContext *ctx); /* RESET {reg} */
int mrt_clear(MCpu *cpu, MContext *ctx); /* CLEAR */
int mrt_in (MCpu *cpu, MContext *ctx); /* IN {reg} */
int mrt_add (MCpu* cpu, MContext* ctx); /* ADD {reg} {reg }*/
int mrt_rcl (MCpu* cpu, MContext* ctx); /* RCL {reg} {reg} */

void MRTAddRuntime (MCpu *cpu);

#endif /* _MRT_H */
