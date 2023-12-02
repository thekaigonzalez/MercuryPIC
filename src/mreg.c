#include "mreg.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
MRegisterInitialize (MReg *reg)
{
  memset (reg->data, 0, MERC_REGISTER_BYTE_MAX * sizeof (int));
  reg->position = 0;
  reg->locked = false;
  reg->owner = 0;
}

void
MRegisterIncrement (MReg *reg)
{
  if (reg)
    {
      reg->data[reg->position]++;
    }
}

void
MRegisterPush (MReg *reg, byte b)
{
  if (reg)
    {
      reg->data[reg->position] = b;
      reg->position++;
    }
}

void
MRegisterPut (MReg *reg, byte b, int pos)
{
  if (reg)
    {
      if (pos >= 0 && pos < MERC_REGISTER_BYTE_MAX)
        {
          reg->data[pos] = b;
        }
    }
}

void
MRegisterIncrementL (MReg *reg, byte ownership)
{
  if (reg)
    {
      if (reg->locked && reg->owner == ownership)
        {
          MRegisterIncrement (reg);
        }
      else
        {
          fprintf (stderr, "%s: permission denied\n", __func__);
          exit (1);
        }
    }
}

void
MRegisterPushL (MReg *reg, byte b, byte ownership)
{
  if (reg)
    {
      if (reg->locked && reg->owner == ownership)
        {
          MRegisterPush (reg, b);
        }
      else
        {
          fprintf (stderr, "%s: permission denied\n", __func__);
          exit (1);
        }
    }
}

void
MRegisterLock (MReg *reg, byte ownership)
{
  if (reg)
    {
      reg->locked = true;
      reg->owner = ownership;
    }
}

void
MRegisterUnlock (MReg *reg, byte ownership)
{
  if (reg)
    {
      if (reg->locked && reg->owner == ownership)
        {
          reg->locked = false;
        }
    }
}

_Bool
MRegisterCompare (MReg *reg1, MReg *reg2)
{
  if (reg1 && reg2)
    {
      for (int i = 0; i < MERC_MEMORY_POOLING_SIZE; i++)
        {
          if (reg1->data[i] != reg2->data[i])
            {
              return false;
            }
        }
      return true;
    }
  return false;
}

byte
MRegisterAtPosition (MReg *reg, int position)
{
  if (reg)
    {
      if (position <= MERC_REGISTER_MAX)
        {
          return reg->data[position];
        }
    }

  return -127;
}
