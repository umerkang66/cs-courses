; PRINTING ON THE NUMBERS ON SCREEN
[org 0x0100]
jmp start


clearscreen: 
  push es
  push ax
  push di

  mov ax, 0xb800
  mov es, ax
  mov di, 0

  nextlocation: 
    mov word [es:di], 0x0720 ; see 11-01, 0x07 is black background and white text
    add di, 2
    cmp di, 4000
    jne nextlocation

  pop di
  pop ax
  pop es
  ret


printscreen: 
  push bp
  mov bp, sp
  push es 
  push ax
  push cx
  push dx
  push di
  
  mov ax, 0xb800
  mov es, ax
  mov di, 0

  mov ax, [bp + 4] ; number to print
  mov bx, 10       ; division base 10
  mov cx, 0        ; total digit counter

  collectdigit: 
    mov dx, 0      ; empty it out
    div bx         ; divides ax by bx, quotient in ax, remainder in dl
    add dl, 0x30   ; converting into ascii
    push dx
    inc cx
    cmp ax, 0
    jnz collectdigit

  printdigit: 
    pop dx
    mov dh, 0x07    ; adding the color code
    mov [es:di], dx ; this is the both part setted dx
    add di, 2
    dec cx
    jnz printdigit

  pop di
  pop dx
  pop cx
  pop ax
  pop es
  mov sp, bp
  pop bp
  
  ret 4


start: 
  call clearscreen

  mov ax, 452
  push ax ; add this arguments
  call printscreen

  ; wait for keypress
  mov ah, 0x1 ; input char is 0x1 in ah
  int 0x21


mov ax, 0x4c00
int 0x21
