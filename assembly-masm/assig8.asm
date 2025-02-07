.model tiny
.code
org 100h
start:
  jmp codepart
  oldvect8 dd (?)
  oldvect15 dd (?)
  is_toggle db 0
codepart: 
  ; interrupt vectors address is stored at segment 0000h
  mov ax, 0
  mov es, ax
  ; store the previous offset and segment address of 8h interrupt
  ; in our variable oldvect8
  mov ax, es:[8h*4]
  mov word ptr cs:oldvect8, ax
  mov ax, es:[8h*4+2]
  mov word ptr cs:oldvect8[2], ax

  mov ax, es:[15h*4]
  mov word ptr cs:oldvect15, ax
  mov ax, es:[15h*4+2]
  mov word ptr cs:oldvect15[2], ax

  ; this interrupt 8h, is called automatically by operating system every 1/18.2 second
  ; add the our proc offset and segment address to the original interrupt
  ; vectors
  mov ax, offset newint8
  mov es:[8h*4], ax
  mov es:[8h*4+2], cs

  mov ax, offset newint15
  mov es:[15h*4], ax
  mov es:[15h*4+2], cs

  ; keep() action
  mov ah, 31H
  mov dx, (end_program - start + 15) / 16  ; Calculate number of paragraphs
  ; there are 16 bytes in a paragraph
  int 21h
newint15 proc near
  cmp ah, 04FH
  jne endint

  cmp al, 23H ; scan code of ctrl
  jne endint

  mov ax, 40H
  mov es, ax
  ; bit test
  mov bl, 00001100b
  ; from left 3rd is ctrl key state, 4th is alt key state
  mov bh, byte ptr es:[17H]
  and bh, bl
  cmp bh, bl
  jne endint
  
  ; Toggle the is_toggle memory variable
  xor byte ptr cs:is_toggle, 1
  
  endint:
  ; go to the original 8h interrupt
  ; this interrupt is called by the os
  ; we don't need to call this ourselves
  jmp dword ptr cs:oldvect15
newint15 endp
newint8 proc near
  push ax
  push es

  ; video memory segment address
  mov ax, 0B800H
  mov es, ax

  cmp byte ptr cs:is_toggle, 0
  jne empty_print

  mov byte ptr es:[0], 'U'
  mov byte ptr es:[1], 07H
  mov byte ptr es:[2], 'M'
  mov byte ptr es:[3], 07H
  mov byte ptr es:[4], 'E'
  mov byte ptr es:[5], 07H
  mov byte ptr es:[6], 'R'
  mov byte ptr es:[7], 07H
  jmp end_print
  
  empty_print:
  mov byte ptr es:[0], ' '
  mov byte ptr es:[1], 07H
  mov byte ptr es:[2], ' '
  mov byte ptr es:[3], 07H
  mov byte ptr es:[4], ' '
  mov byte ptr es:[5], 07H
  mov byte ptr es:[6], ' '
  mov byte ptr es:[7], 07H

  end_print:
  pop es
  pop ax

  ; go to the original 8h interrupt
  ; this interrupt is called by the os
  ; we don't need to call this ourselves
  jmp dword ptr cs:oldvect8
newint8 endp

end_program:
end start
