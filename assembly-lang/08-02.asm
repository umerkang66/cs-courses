; SHIFT OPERATIONS: 8 Bit Multiplication, in the 8 Bit Register
[org 0x0100]

jmp start

; 4 bit numbers, need space 8 bit for multiplication
multiplicand: db 0xC8 ; 200 = 0b 11001000
multiplier:   db 0x32 ; 0   = 0b 00110010
result:       dw 0    ; should be 10000 = '0x2710'


start:
  mov cl, 8 ; loop will run 8 times, because there are 8 digits
  mov dl, [multiplier]

  checkbit: 
    shr dl, 1 ; right shift dl
    jnc skip ; jump if carry is not set,
      mov al, [multiplicand]
      add byte [result], al
      mov al, [multiplicand + 1] ; this is byte
      adc byte [result + 1], al; add also includes previous carry

    skip: ; if we divide only collect the multiplicand as 1 byte, not 2 bytes (16-bit register), and the multiplicand is also a 2 8-bits number, multiplying it with another 8-bit number, results into more than 8-bits
      shl byte [multiplicand], 1
      rcl byte [multiplicand + 1], 1

  dec cl
  jnz checkbit


mov ax, 0x4c00 ; exit code ..
int 0x21 ; .. is what the OS should do for me
