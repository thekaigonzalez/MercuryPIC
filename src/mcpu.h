// $Id: mreg.h

#ifndef _MCPU_H
#define _MCPU_H

#include "mctx.h"
#include "mreg.h"
#include "msec.h"

typedef struct MByteOp MByteOp;

typedef struct MCPU MCpu;

typedef struct
{
  byte id;
  int (*function) (MReg *reg, MCpu *cpu);
} MSysCall;

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

  /* syscalls */
  MSysCall **systemcall;
  int systemcall_count;
  int systemcall_capacity;
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

MSysCall *MSysCallCreate (MMemoryPool *pool, byte id,
                          int (*function) (MReg *reg, MCpu *cpu));
byte MSysCallRetId (MSysCall *call);
int (*MSysCallRetFunction (MSysCall *call)) (MReg *reg, MCpu *cpu);

MSysCall* MSysCallFind (MCpu *cpu, byte id);
void MAddSyscall (MCpu *cpu, byte id, int (*function) (MReg *reg, MCpu *cpu));

void MCpuDestroy (MCpu *cpu);

#endif /* _MCPU_H */
