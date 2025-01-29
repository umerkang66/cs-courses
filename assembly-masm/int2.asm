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
  mov ax, es:[8h*4]
  mov word ptr cs:oldvect, ax
  mov ax, es:[8h*4+2]
  mov word ptr cs:oldvect[2], ax

  ; add the our proc offset and segment address to the original interrupt
  ; vectors
  mov ax, offset myproc
  mov es:[8h*4], ax
  mov es:[8h*4+2], cs

  ; keep() action
  mov ah, 31H
  mov dx, (end_program - start + 15) / 16  ; Calculate number of paragraphs
  ; there are 16 bytes in a paragraph
  int 21h

myproc proc near
  push ax
  push es

  ; video memory segment address
  mov ax, 0B800H
  mov es, ax

  mov byte ptr es:[0], 'Y'
  mov byte ptr es:[1], 07H
  mov byte ptr es:[2], 'o'
  mov byte ptr es:[3], 07H
  mov byte ptr es:[4], 'u'
  mov byte ptr es:[5], 07H

  pop es
  pop ax

  ; go to the original 8h interrupt
  ; this interrupt is called by the os
  ; we don't need to call this ourselves
  jmp dword ptr cs:oldvect
myproc endp

end_program:
end start
