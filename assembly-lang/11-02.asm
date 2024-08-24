; PRINTING ON THE SCREEN
[org 0x0100]

jmp start

message: db "Hello World!"
length: dw 12


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
  push si
  push di
  
  mov ax, 0xb800
  mov es, ax
  mov di, 0

  mov si, [bp + 6] ; string
  mov cx, [bp + 4] ; length
  mov ah, 0x07 ; to print there are value things, one is ascii value that is in the lower part of 2 byte, and style at the higher part of 2 byte, here we are setting the higher part of 'ax'

  nextchar: 
    mov al, [si] ; here we are settings the higher part of 'ax'
    mov [es:di], ax ; this is the both part setted ax
    add di, 2
    add si, 1
    dec cx
    jnz nextchar

  pop di
  pop si
  pop cx
  pop ax
  pop es
  mov sp, bp
  pop bp
  
  ret 4


start: 
  call clearscreen

  mov ax, message
  push ax ; add these two arguments
  push word [length]
  call printscreen

  ; wait for keypress
  mov ah, 0x1 ; input char is 0x1 in ah
  int 0x21


mov ax, 0x4c00
int 0x21
