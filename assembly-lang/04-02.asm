[org 0x0100]

  xor ax, ax

  ; store the num1 add at bx
  mov bx, num1
  mov cx, 3 ; 3 times the loop will run


  outerloop: ; loop will run by using cx value
    add ax, [bx]
    add bx, 2

    sub cx, 1
    jnz outerloop ; jnz = jump if 'zero-flag' is not set, 3-1=2, zf will be 0, 2-1=1, zf will be 0, 1-1=0, zf will be 1, jnz stands for 'jump if not zero'


  mov [bx], ax

  mov ax, 0x4c00 ; exit code ..
  int 0x21 ; .. is what the OS should do for me


num1: dw 5, 10, 15, 0
