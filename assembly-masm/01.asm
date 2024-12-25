.model small

; create the data segment and 
; assign a string to st1 variable
; each letter of string will create
; a byte (because of db) in memory
data_seg segment 'data'
  st1 db "Muhammad Umer", 13, 10, '$'
data_seg ends

; we are currently not using any stack
stack_seg segment 'stack'
  dw 100 DUP(?)
stack_seg ends

; code segment
code_seg segment 'code'
  assume cs:code_seg, ds:data_seg, ss:stack_seg
main proc far
  ; adding dataseg address in datasegment register
  mov ax, data_seg
  mov ds, ax

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

  ; printing the string
  mov dx, offset st1
  mov ah, 9
  int 21h

  ; exit the program
  mov ah, 04ch
  int 21h

main endp
code_seg ends

; starting point of the program
end main
