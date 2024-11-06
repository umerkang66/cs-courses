.model small

data_seg segment 'data'
  st1 db "Hello World!", 13, 10, '$'
data_seg ends

stack_seg segment 'stack'
  dw 100 DUP(?)
stack_seg ends

code_seg segment 'code'
  assume cs:code_seg, ds:data_seg, ss:stack_seg
main proc far
  mov ax, data_seg
  mov ds, ax

  mov dx, offset st1
  mov ah, 9
  int 21h

  mov ah, 4ch
  int 21h
main endp
code_seg ends

end main ; set the entry point of the program
