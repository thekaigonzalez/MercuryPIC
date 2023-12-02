; $Id: compare.asm

[compat mercury] ; actually MercuryPIC

t:
  echo 'A'

f:
  echo 'B'

m:
  push R1,0x47,1
  push R2,0x48,1
  cmp R1,R2,t,f
