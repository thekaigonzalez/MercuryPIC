; $Id: sycall.asm

m:
  mov R1,'A'
  mov R1,'B'
  mov R1,'C'
  mov R1,0x0a

; call sys_write
  int R1,0xEE
