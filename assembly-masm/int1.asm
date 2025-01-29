.model tiny 
.code
org 100h
jmp codepart
  oldvect dd (?)
  st1 db "This is int 65H", 13, 10, '$'
codepart: 
  mov ax, 00h
  mov es, ax

  ; store the old 65h address into the old vect
  mov ax, es:[65h*4]
  mov word ptr cs:oldvect, ax
  mov ax, es:[65h*4+2]
  mov word ptr cs:oldvect[2], ax

  ; store the my proc address in the int65 vector
  mov ax, offset myproc
  mov es:[65H*4], ax   ; offset address of my proc
  mov es:[65H*4+2], cs  ; segment address of my proc

  ; so that when int 65 is called, always my proc will be called
  int 65H

  mov ah, 31H
  mov dx, 100H
  mov al, 0
  int 21H
myproc proc near
  push ds
  push dx
  push ax
  mov ax, cs
  mov ds, ax
  mov dx, offset st1
  mov ah, 9
  int 21H
  pop ax
  pop dx
  pop ds
  iret
myproc endp
end codepart
