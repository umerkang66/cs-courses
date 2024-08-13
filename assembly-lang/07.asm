; SORTING: Bubble Sort in Assembly

[org 0x0100]

jmp start

data: dw 10, 5, 15, 0

start:
  mov ax, 0
  mov cx, 3 ; total number of data el are 4, and it should 4-1 3 times
  

  outerloop: ; loop will run by using cx value
    mov bx, 0

    innerloop: 
      mov ax, [data + bx]
      cmp ax, [data + bx + 2]

      jbe noswap ; jump if ax, value is "below or equal" to data + bx + 2, next value, if it is below, or equal it is at the right place

      ; otherwise, Swapping Logic
      mov dx, [data + bx + 2]
      ; adding in the memory
      mov [data + bx + 2], ax
      mov [data + bx], dx

      noswap:
        add bx, 2
        cmp bx, 6 ; this should i times, means 3 times, == 6
        jne innerloop

    sub cx, 1    
    jnz outerloop ; jump if not zero to 'outerloop'


  mov ax, 0x4c00 ; exit code ..
  int 0x21 ; .. is what the OS should do for me
