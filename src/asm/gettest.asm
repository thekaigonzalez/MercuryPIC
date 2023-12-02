; $Id: gettest.asm

[compat mercury] ; well, we're actually using MercuryPIC, but it's
                 ; compatible with NexFUSE

m:
  push R1,0x47,1
  pop R1,1,R2
  each R2
