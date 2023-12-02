// $Id: mdef.h

#ifndef _MDEF_H
#define _MDEF_H

#include "mvar.h"

// OpenLUD ByteCode functinos
#define _NULL (byte)0xAF
#define ECHO (byte)40
#define MOVE (byte)41
#define EACH (byte)42
#define RESET (byte)43
#define CLEAR (byte)44
#define PUT (byte)45
#define GET (byte)46
#define ADD (byte)47
#define LAR (byte)48
#define LSL (byte)49
#define IN (byte)50
#define CMP (byte)51
#define INC (byte)52
#define REP (byte)53
#define RCL (byte)54
#define INT (byte)55

#define SUB (byte)10
#define ENDSUB (byte)0x80
#define GOSUB (byte)15

// initialize and end
#define INIT (byte)100
#define INITSEC (byte)70
#define END (byte)22

#endif /* _MDEF_H */
