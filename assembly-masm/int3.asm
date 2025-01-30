.model tiny
.code
org 100h
start:
  jmp codepart
  oldvect dd (?)
codepart: 
  ; interrupt vectors address is stored at segment 0000h
  mov ax, 0
  mov es, ax
  ; store the previous offset and segment address of 8h interrupt
  ; in our variable oldvect
  mov ax, es:[15H*4]
  mov word ptr cs:oldvect, ax
  mov ax, es:[15H*4+2]
  mov word ptr cs:oldvect[2], ax

  ; add the our proc offset and segment address to the original interrupt
  ; vectors
  mov word ptr es:[15H*4], offset newint15
  mov word ptr es:[15H*4+2], cs

  mov ah, 01
  int 21h
  mov dl, al
  mov ah, 02
  int 21h

  ; keep() action
  mov ah, 31H
  mov dx, (end_program - start + 15) / 16  ; Calculate number of paragraphs
  ; there are 16 bytes in a paragraph
  int 21h

newint15 proc near
  cmp ah, 04FH
  jne endint

  cmp al, 1EH ; scan code of A
  jne endint
  mov al, 2CH
  
  endint:
  ; go to the original 8h interrupt
  ; this interrupt is called by the os
  ; we don't need to call this ourselves
  jmp dword ptr cs:oldvect
newint15 endp

end_program:
end start
