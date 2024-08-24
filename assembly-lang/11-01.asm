; PRINTING ON THE SCREEN
[org 0x0100]


mov ax, 0xb800  ; video memory base
mov es, ax      ; can't directly move to es
mov di, 0       ; top left location


; there are 25 x 80 plane in the dosbox (16bit) screen, so there are about 2000 cells(25 * 80), and each cells contain of 2 bytes so there 4000 bytes
nextpos: 
  mov word [es:di], 0x0720 ; 0x07 -- full white, 0x20 is the space character
  add di, 2
  cmp di, 4000
  jne nextpos


mov ax, 0x4c00
int 0x21
