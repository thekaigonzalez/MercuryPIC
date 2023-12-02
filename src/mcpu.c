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

void
MCpuDestroy (MCpu *cpu)
{
  if (cpu)
    {
      MPoolDestroy (cpu->blk);
    }
}
