// $Id: mtest.c

#include "mbyte.h"
#include "mcpu.h"
#include "mctx.h"
#include "mpool.h"
#include "mreg.h"
#include "mrunl.h"
#include "mvar.h"

#include <assert.h>

#define pass() fprintf (stdout, "test %s passed\n", __func__)
#define fail() fprintf (stdout, "test %s failed\n", __func__)

int
test_memory_pooling (void)
{
  MMemoryPool *root = MPoolCreate (MERC_MEMORY_POOLING_SIZE);
  MByteList *list = MByteListNew (root);

  MByteListAdd (list, 1);
  MByteListAdd (list, 2);
  MByteListAdd (list, 3);

  byte *bytes = MByteListCopy (list);

  assert (bytes[0] == 1);
  assert (bytes[1] == 2);
  assert (bytes[2] == 3);

  MPoolDestroy (root);
  pass ();
  return 0;
}

int
test_byte_list (void)
{
  MMemoryPool *root = MPoolCreate (MERC_MEMORY_POOLING_SIZE);
  MByteList *list = MByteListNew (root);

  MByteListAdd (list, 1);
  MByteListAdd (list, 2);
  MByteListAdd (list, 3);

  byte *bytes = MByteListCopy (list);

  assert (bytes[0] == 1);
  assert (bytes[1] == 2);
  assert (bytes[2] == 3);

  MPoolDestroy (root);
  pass ();
  return 0;
}

int
test_register (void)
{
  MReg register1;
  MRegisterInitialize (&register1);

  register1.data[0] = 1;
  register1.data[1] = 2;
  register1.data[2] = 3;

  assert (register1.data[0] == 1);
  assert (register1.data[1] == 2);
  assert (register1.data[2] == 3);

  pass ();
  return 0;
}

int
test_cpu (void)
{
  MCpu cpu;

  MRegisterInitialize (&cpu.registers[0]);

  MRegisterIncrement (&cpu.registers[0]);

  assert (cpu.registers[0].data[0] == 1);

  pass ();
  return 0;
}

int
test_ctx (void)
{
  MMemoryPool *root = MPoolCreate (MERC_MEMORY_POOLING_SIZE);
  MByteList *list = MByteListNew (root);

  MByteListAdd (list, 1);

  MContext *ctx = MContextNew (root, list);

  MByteListClear (list);

  /*byte list retained in ctx (primarily for functions that use it)*/

  assert (MContextGet (ctx, 0) == 1);
  assert (MByteListGetSize (list) == 0);

  MPoolDestroy (root);

  pass ();
  return 0;
}

int
test_function (MCpu *c, MContext *ctx)
{
  c->registers[0].data[0] = 1;
  return 0;
}

int
test_cpu_byteop (void)
{
  MCpu cpu;

  MCpuInitialize (&cpu);

  MCpuAddByteOp (&cpu, 71, test_function);

  MCpuGetByteOpFunction (&cpu, 71) (&cpu, NULL);

  assert (cpu.registers[0].data[0] == 1);

  MPoolDestroy (cpu.blk);

  pass ();

  return 0;
}

int
sys_print (MCpu *cpu, MContext *ctx)
{
  int value = (int)MContextGet (ctx, 1);

  printf ("%c\n", value);

  return 0;
}

int
test_runner (void)
{
  MCpu cpu;

  MCpuInitialize (&cpu);

  MByteList *list = MByteListNew (cpu.blk);

  MByteListAdd (list, 10);
  MByteListAdd (list, 65);
  MByteListAdd (list, 45);
  MByteListAdd (list, 46);
  MByteListAdd (list, 0);
  MByteListAdd (list, 22);
  MByteListAdd (list, ENDSUB);
  MByteListAdd (list, 15);
  MByteListAdd (list, 65);
  MByteListAdd (list, 0);
  MByteListAdd (list, 22);

  MCpuAddByteOp (&cpu, 45, sys_print);

  MRunByteList (&cpu, list);

  MCpuDestroy (&cpu);

  pass ();
  return 0;
}

int
test_2byte_list (void)
{
  MMemoryPool *root = MPoolCreate (MERC_MEMORY_POOLING_SIZE);
  MByteList *list = MByteListNew (root);

  MByteListAdd (list, 1);
  MByteListAdd (list, 2);
  MByteListAdd (list, 3);
  MByteListAdd (list, 4);
  MByteListAdd (list, 5);
  MByteListAdd (list, 6);

  byte *bytes = MByteListCopy (list);

  assert (bytes[0] == 1);
  assert (bytes[1] == 2);
  assert (bytes[2] == 3);
  assert (bytes[3] == 4);
  assert (bytes[4] == 5);
  assert (bytes[5] == 6);

  MPoolDestroy (root);

  pass ();
  return 0;
}

int
main (void)
{
  test_memory_pooling ();
  test_byte_list ();
  test_register ();
  test_cpu ();
  test_ctx ();
  test_cpu_byteop ();
  test_runner ();
  test_2byte_list ();
}
