[org 0x0100]

jmp start
  ; now this will be created as variables
  num1: dw 5, 10, 15, 0
  result: dw 0

start:
  xor ax, ax ; set the ax = 0
  ; store the num1 add at bx
  mov bx, 0


  outerloop: ; loop will run by using cx value
    add ax, [num1 + bx]
    add bx, 2

    cmp bx, 6 ; when bx==6, result is 0, zf i set, now loop can stop by both jnz, and jne
    jne outerloop ; jne "jump if not equal", jump if previous result is not equal


  mov [result], ax

  mov ax, 0x4c00 ; exit code ..
  int 0x21 ; .. is what the OS should do for me
