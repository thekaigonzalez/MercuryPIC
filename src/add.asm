; $Id: add.asm

[compat mercury]

m:
  mov R1,5
  mov R1,10
  add R1,R2
; result of 5+10 saved to R2(0)
; note: this code ONLY works with MercuryPIC, as line endings in other bytecode
; formats is 0, which prevents this code below from working correctly
  rcl R2,0
