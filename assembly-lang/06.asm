[org 0x0100]

jmp start
  ; now this will be created as variables
  ; we are creating these as variables, but computer will use these as instructions, so jump to the start
  ; if these variables are at the end, these variables can't mess with our code, whatever these instructions are after our code, we don't care
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
