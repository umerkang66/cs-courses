; FUNCTIONS: or SUBROUTINES
[org 0x0100]

jmp start
data: dw 60, 55, 40, 50
swap: db 0


bubblesort: 
  dec cx ; cx is set in start function
  shl cx, 1 ; because we are using words not bytes for numbers, so it will double the cx value

  mainloop: 
    mov si, 0 ; use as array index
    mov byte [swap], 0 ; only start next iteration if there is a swap

    innerloop: 
      mov ax, [bx + si]
      cmp ax, [bx + si + 2]
      jbe noswap

        ; swapping logic
        mov dx, [bx + si + 2]
        mov [bx + si], dx
        mov [bx + si + 2], ax
        mov byte [swap], 1

      noswap:
        add si, 2
        cmp si, cx
        jne innerloop

    cmp byte [swap], 1 ; if there is a swap
    je mainloop

  ret ; this will return from where it was called


start: 
  mov bx, data
  mov cx, 4 ; length of elements (array)

  ; make a function call
  call bubblesort
  ; data is now sorted

mov ax, 0x4c00 ; exit code ..
int 0x21 ; .. is what the OS should do for me
