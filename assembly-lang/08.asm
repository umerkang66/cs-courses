; SHIFT OPERATIONS: 4 Bit Multiplication
[org 0x0100]

jmp start

; 4 bit numbers, need space 8 bit for multiplication
multiplicand: db 13 
multiplier:   db 5
result:       db 0


start:
  mov cl, 4 ; loop will run 4 times, because there are 4 digits
  mov bl, [multiplicand]
  mov dl, [multiplier]

  checkbit: 
    shr dl, 1 ; right shift dl
    jnc skip ; jump if carry is not set,
      add [result], bl; else if carry is set mean there is 1, add multplicand to the result

    skip: ; this instruction will run in both cases if carry is set or not, just if carry is set we skip the previous add[result] instruction
      shl bl, 1 ; left shift bl

  dec cl
  jnz checkbit


mov ax, 0x4c00 ; exit code ..
int 0x21 ; .. is what the OS should do for me
