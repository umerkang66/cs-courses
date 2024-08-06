[org 0x0100]

  ; start of code
  mov ax, [num1] ; move the constant 5 into register ax
  mov bx, [num2]

  add ax, bx ; add value of bx into the value of ax

  mov bx, [num3]
  add ax, bx

  mov [num4], ax

  mov ax, 0x4c00 ; exit code ..
  int 0x21 ; .. is what the OS should do for me


num1: dw 5
num2: dw 10
num3: dw 15
num4: dw 0

; we can also only assign and num1, and move to other addresses by num1+2, num1+4, num1+6, ... respectively, because addresses in ram by 'dw' command are 2 bytes
