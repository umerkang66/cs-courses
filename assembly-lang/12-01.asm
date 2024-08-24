; PRINTING ON THE NUMBERS ON SCREEN
[org 0x0100]
jmp start


clearscreen: 
  push es
  push ax
  push cx
  push di

  mov ax, 0xb800
  mov es, ax
  mov di, 0
  mov ax, 0x0765
  mov cx, 2000

  cld          ; auto-increment mode, clear the direction flag, set means auto-decrement
  rep stosw    ; rep cx times, store words
               ; source is ax for word, al for byte
               ; destination is es:di
               ; inc/dec di by 2 bytes

  pop di
  pop cx
  pop ax
  pop es
  ret


start: 
  call clearscreen


mov ax, 0x4c00
int 0x21
