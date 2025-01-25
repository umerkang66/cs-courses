.model small

data_seg segment 'data'
  st1 db "Enter a 3 digit Num: $"
  st2 db 13, 10, "Enter a 1 digit Num: $"
  st3 db 13, 10, "Operation +, -, *, / : $"
  st4 db 13, 10, "Result: $"
  multiplicant db 0
  digit1 db 50 DUP (?)
  digit2 db 1 DUP (?)
  operation db 1 DUP (?)
data_seg ends

stack_seg segment 'stack'
  dw 100h DUP(?)
stack_seg ends

code_seg segment 'code'
  assume cs:code_seg, ds:data_seg, ss:stack_seg
main proc far
  mov ax, data_seg
  mov ds, ax

  mov ah, 09h
  mov dx, offset st1
  int 21h

  mov digit1[0], 4
  mov dx, offset digit1
  mov ah, 0ah
  int 21h
  mov bl, digit1[1]; bx = count
  mov bh, 00h
  mov digit1[bx+2], '$'

  ; convert three digit number into one number in register
  mov bx, 4
  mov dh, 1
  mov cx, 3
  loop_body:
    sub digit1[bx], 30h
    mov al, digit1[bx]
    mul dh
    add multiplicant, al
    mov al, dh
    mov dl, 10
    mul dl
    mov dh, al
    dec bx
    dec cx
    cmp cx, 0
    jg loop_body
  
  ; now multiplicant has the 3 digit number in integer hex form

  mov ah, 09h
  mov dx, offset st2
  int 21h

  mov ah, 01h
  int 21h
  mov digit2, al

  mov ah, 09h
  mov dx, offset st3
  int 21h

  mov ah, 01h
  int 21h
  mov operation, al

  mov ah, 04ch
  int 21h

main endp
code_seg ends

end main
