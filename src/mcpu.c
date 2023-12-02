#include "mcpu.h"
#include "mbyte.h"
#include "mvar.h"

void
MCpuInitialize (MCpu *cpu)
{
  MMemoryPool *root = MPoolCreate (MERC_MEMORY_POOLING_SIZE);

  for (int i = 0; i < MERC_REGISTER_MAX; i++)
    {
      MRegisterInitialize (&cpu->registers[i]);
      MSectionInitialize (&cpu->sections[i]);
    }

  cpu->op = MPoolAlloc (root, MERC_MEMORY_POOLING_SIZE * sizeof (MByteOp));
  cpu->op_count = 0;
  cpu->op_capacity = MERC_MEMORY_POOLING_SIZE;
  cpu->blk = root;

  cpu->systemcall
      = MPoolAlloc (root, MERC_MEMORY_POOLING_SIZE * sizeof (MSysCall));
  cpu->systemcall_count = 0;
  cpu->systemcall_capacity = MERC_MEMORY_POOLING_SIZE;
}

void
MCpuAddByteOp (MCpu *cpu, byte id, int (*function) (MCpu *cpu, MContext *ctx))
{
  if (cpu)
    {
      if (cpu->op_count == cpu->op_capacity)
        {
          cpu->op_capacity += MERC_MEMORY_POOLING_SIZE;
          cpu->op = MPoolRealloc (cpu->blk, cpu->op,
                                  cpu->op_capacity * sizeof (MByteOp));
        }

      cpu->op[cpu->op_count] = MCpuCreateByteOp (cpu, id, function);

      cpu->op_count++;
    }
}

MByteOp *
MCpuCreateByteOp (MCpu *cpu, byte id,
                  int (*function) (MCpu *cpu, MContext *ctx))
{
  MByteOp *op = MPoolAlloc (cpu->blk, sizeof (MByteOp));

  op->id = id;
  op->function = function;

  return op;
}

int (*MCpuGetByteOpFunction (MCpu *cpu, byte id)) (MCpu *cpu, MContext *ctx)
{
  if (cpu)
    {
      for (int i = 0; i < cpu->op_count; i++)
        {
          if (cpu->op[i])
            {
              if (cpu->op[i]->id == id)
                {
                  return cpu->op[i]->function;
                }
            }
        }
    }
  return NULL;
}

MReg *
MRegister (MCpu *cpu, int position)
{

  if (cpu && position >= 0 && position < MERC_REGISTER_MAX)
    {
      return &cpu->registers[position];
    }

  return NULL;
}

MSysCall *
MSysCallFind (MCpu *cpu, byte id)
{
  if (cpu)
    {
      for (int i = 0; i < cpu->systemcall_count; i++)
        {
          if (cpu->systemcall[i] && cpu->systemcall[i]->id == id)
            {
              return cpu->systemcall[i];
            }
        }
    }
  return NULL;
}

void
MAddSyscall (MCpu *cpu, byte id, int (*function) (MReg *reg, MCpu *cpu))
{
  if (cpu)
    {
      if (cpu->systemcall_count == cpu->systemcall_capacity)
        {
          cpu->systemcall_capacity += MERC_MEMORY_POOLING_SIZE;
          cpu->systemcall
              = MPoolRealloc (cpu->blk, cpu->systemcall,
                              cpu->systemcall_capacity * sizeof (MSysCall));
        }

      cpu->systemcall[cpu->systemcall_count]
          = MSysCallCreate (cpu->blk, id, function);

      cpu->systemcall_count++;
    }
}

MSysCall *
MSysCallCreate (MMemoryPool *pool, byte id,
                int (*function) (MReg *reg, MCpu *cpu))
{
  MSysCall *call = MPoolAlloc (pool, sizeof (MSysCall));

  call->id = id;
  call->function = function;

  return call;
}

byte
MSysCallRetId (MSysCall *call)
{
  if (call)
    {
      return call->id;
    }

  return 0;
}

int (*MSysCallRetFunction (MSysCall *call)) (MReg *reg, MCpu *cpu)
{
  if (call)
    {
      return call->function;
    }

  return NULL;
}

void
MCpuDestroy (MCpu *cpu)
{
  if (cpu)
    {
      MPoolDestroy (cpu->blk);
    }
}
