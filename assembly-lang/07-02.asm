; SORTING: Bubble Sort in Assembly, More Efficient than previous one

[org 0x0100]

jmp start

data: dw 0, 10, 5, 15
swap: db 0 ; use this to find if there was some swap in inner loop

start:
  mov ax, 0
  

  outerloop: ; loop will run by using cx value
    mov bx, 0
    mov byte [swap], 0

    innerloop: 
      mov ax, [data + bx]
      cmp ax, [data + bx + 2]

      jbe noswap ; jump if ax, value is "below or equal" to data + bx + 2, next value, if it is below, or equal it is at the right place

        ; otherwise, Swapping Logic
        mov dx, [data + bx + 2]
        ; adding in the memory
        mov [data + bx + 2], ax
        mov [data + bx], dx
        mov byte [swap], 1

      noswap:
        add bx, 2
        cmp bx, 6 ; this should i times, means 3 times, == 6
        jne innerloop

    cmp byte [swap], 1
    je outerloop


mov ax, 0x4c00 ; exit code ..
int 0x21 ; .. is what the OS should do for me
