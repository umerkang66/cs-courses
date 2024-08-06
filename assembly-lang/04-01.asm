[org 0x0100]

  xor ax, ax

  ; store the num1 add at bx
  mov bx, num1

  add ax, [bx]
  add bx, 2

  add ax, [bx]
  add bx, 2

  add ax, [bx]
  add bx, 2

  mov [bx], ax

  mov ax, 0x4c00 ; exit code ..
  int 0x21 ; .. is what the OS should do for me


num1: dw 5, 10, 15, 0
