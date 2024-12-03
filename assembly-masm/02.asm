.model small

data_seg segment 'data'
  st1 db 53 (?) ; first for size, second for length, and last for '$', 13, 10s
  st2 db "Enter your fullname: $"
data_seg ends

; we are not using the stack
stack_seg segment 'stack'
  dw 100 DUP(?)
stack_seg ends

code_seg segment 'code'
  assume cs:code_seg, ds:data_seg, ss:stack_seg
main proc far
  ; for storing the data segment address in the data segment register
  mov ax, data_seg
  mov ds, ax

  mov dx, offset st2
  mov ah, 9 ; service routine code for printing the string
  int 21h

  mov st1[0], 50 ; total size of string, no more than 50 characters can be stored
  mov dx, offset st1
  mov ah, 0ah
  int 21h

  ; adding the dollar sign
  mov bl, st1[1]
  mov bh, 0
  mov st1[bx + 2], '$'
  ; mov st1[bx + 3], 13
  ; mov st1[bx + 4], 10

  ; CHANGING THE CURSOR
  mov ah, 06h
  mov al, 25   ; mov 25 lines
  mov bh, 07h
  mov cx, 0000h ; upper left row=0, upper left col = 0, so 00 for ch, 00 for cl
  mov dx, 184Fh ; lower right row=24, lower right col=79
  int 10h 

  ; change the cursor position
  mov bh, 0  ; page no. 0
  mov dh, 12 ; total rows = 25, half = 25/2
  mov dl, 33 ; total cols = 80, half = 80/2 = 40 - (string length / 2) 7 = 33
  mov ah, 02
  int 10h    ; 10h/02 is the subroutine code of changing the cursor

  ; printing
  mov dx, offset st1[2]
  mov ah, 9
  int 21h

  ; exiting the program
  mov ah, 04ch
  int 21h

main endp
code_seg ends
end main
