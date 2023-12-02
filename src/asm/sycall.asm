; $Id: sycall.asm

; SYSCALLS are only supported in MercuryPIC,
; syscalls are ways to call functions in which are not prepended by the Mercury
; Runtime.
; these are good for performance, when raw data handling is needed

[compat mercury]

m:
  mov R1,'A'
  mov R1,'B'
  mov R1,'C'
  mov R1,0x0a

; call sys_write
  int R1,0xEE
