// $Id: mreg.h

#ifndef _MREG_H
#define _MREG_H

#include "mvar.h"
#include <stdbool.h>

/*defines a register*/

typedef struct MReg MReg;

struct MReg
{
  /* contains held data for a simple byte-sized register */
  byte data[MERC_REGISTER_BYTE_MAX];

  /* the position of the register, put commands do not affect this*/
  int position;

  /*true if the register is locked, meaning that no changes can be made unless
   * by the owner*/
  _Bool locked;

  byte owner; /*owner of the register, used for locking*/
};

void MRegisterInitialize (MReg *reg);
void MRegisterIncrement (MReg *reg);
void MRegisterPush (MReg *reg, byte b);
void MRegisterPut (MReg *reg, byte b, int pos);

void MRegisterIncrementL(MReg *reg, byte ownership);
void MRegisterPushL(MReg *reg, byte b, byte ownership);

/*locks a register, essentially forcing it to only be used by the owner, AKA
requiring a label to be passed in before it can be modified*/
void MRegisterLock (MReg *reg, byte ownership);
/*unlocks a register*/
void MRegisterUnlock (MReg *reg, byte ownership);

_Bool MRegisterCompare (MReg *reg1, MReg *reg2);

byte MRegisterAtPosition (MReg *reg, int position);

#endif
