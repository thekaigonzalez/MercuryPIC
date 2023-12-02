; $Id: bitwise.asm

m:
; bitwise operations
; shift 300 << 1

; add 47
  mov R1,300
; add 48
  mov R1,1

; call sys_shift0
; the same as: 300 << 1
  int R1,0xEF

  rcl R1,0
