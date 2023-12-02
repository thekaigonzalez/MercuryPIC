#include "msyscalls.h"

int
merc_sys_write (MReg *regist, MCpu *cpu)
{
  for (int i = 0; i < MERC_REGISTER_BYTE_MAX; i++) {
    if (regist->data[i] != 0) {
      printf("%c", regist->data[i]);
    }
  }

  return 0;
}
