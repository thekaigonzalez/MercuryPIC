// $Id: mreg.h

#ifndef _MCPU_H
#define _MCPU_H

#include "mctx.h"
#include "mreg.h"
#include "msys.h"
#include "msec.h"

typedef struct MByteOp MByteOp;

typedef struct MCPU
{
  /* using stack, because allocating all registers and sections on the heap
  costs too much */
  MReg registers[MERC_REGISTER_MAX];
  MSection sections[MERC_SECTION_MAX];

  /* functions */
  MByteOp **op;
  int op_count;
  int op_capacity;

  /* memory*/
  MMemoryPool *blk;
} MCpu;

struct MByteOp
{
  byte id;
  int (*function) (MCpu *cpu, MContext *ctx);
};

void MCpuInitialize (MCpu *cpu);
void MCpuAddByteOp (MCpu *cpu, byte id,
                    int (*function) (MCpu *cpu, MContext *ctx));
MByteOp *MCpuCreateByteOp (MCpu *cpu, byte id,
                           int (*function) (MCpu *cpu, MContext *ctx));
int (*MCpuGetByteOpFunction (MCpu *cpu, byte id)) (MCpu *cpu, MContext *ctx);
MReg *MRegister (MCpu *cpu, int position);
void MCpuDestroy (MCpu *cpu);

#endif /* _MCPU_H */
