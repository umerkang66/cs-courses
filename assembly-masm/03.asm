.model small

data_seg segment 'data'
  character db 'A'
  blank_character db ' '
  row db 12
  col db 38
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
  
  ; clearing the screen
  mov al, 25   ; mov 25 lines
  mov bh, 07h
  mov cx, 0000h ; upper left row=0, upper left col = 0, so 00 for ch, 00 for cl
  mov dx, 184Fh ; lower right row=24, lower right col=79
  mov ah, 06h
  int 10h 

  ; change the cursor position
  mov bh, 0   ; page no. 0
  mov dh, row ; total rows = 25, half = 25/2
  mov dl, col ; total cols = 80, half = 80/2 = 40 - (string length / 2) 7 = 33
  mov ah, 02  ; service routine code for changing cursor
  int 10h     ; 10h/02 is the subroutine code of changing the cursor

  ; printing the character
  mov dl, character
  mov ah, 02
  int 21h


  animation_loop:
    ; check for key press
    mov ah, 0 ; int 16h code for 
    int 16h    ; bios interrupt, key press scan code should be in al
    cmp al, 1Bh; Escape Key
    je near_exit_instruction
    ; if not exited

    ; if upper arrow is pressed 
    cmp al, 48h ; scan code for upper arrow
    je upper_arrow
    cmp al, 50h ; scan code for down arrow
    je down_arrow
    cmp al, 4Dh ; scan code for right arrow
    je right_arrow
    cmp al, 4Bh ; scan code for left arrow
    je left_arrow

    ; if arrow key is not pressed, keep checking for further key presses
    jmp animation_loop
    
    upper_arrow: 
      cmp row, 0  ; if row is already 0, don't move
      je animation_loop
      ; if row is not equal to 0, mov up

      ; CLEAR THE PREVIOUS CHARACTER
      call clear_character

      dec row
      jmp print_new_char
    
    down_arrow: 
      cmp row, 25 ; if row is already 25, don't move
      je animation_loop
      ; if row is not equal to 25, mov up

      ; CLEAR THE PREVIOUS CHARACTER
      call clear_character

      inc row
      jmp print_new_char

; don't worry this will not run after down_arrow instruction 
; because there is a jmp to print_new_char in the end of program
near_exit_instruction: 
  jmp exit_program

    right_arrow: 
      cmp col, 79  ; if col is already 79, don't move
      je animation_loop
      ; if col is not equal to 79, mov up

      ; CLEAR THE PREVIOUS CHARACTER
      call clear_character
      
      inc col
      jmp print_new_char

    left_arrow: 
      cmp col, 0  ; if col is already 0, don't move
      je animation_loop
      ; if col is not equal to 0, mov up

      ; CLEAR THE PREVIOUS CHARACTER
      call clear_character

      dec col
      jmp print_new_char

  
  print_new_char: 
    ; change the cursor position
    mov bh, 0   ; page no. 0
    mov dh, row ; what current row is
    mov dl, col ; what current col is
    mov ah, 02  ; service routine code for changing cursor
    int 10h     ; 10h/02 is the subroutine code of changing the cursor
    ; printing the blank character
    mov dl, character
    mov ah, 02
    int 21h
    ; jump to animation loop for further key presses
    jmp animation_loop


  clear_character:
    ; CLEAR THE PREVIOUS CHARACTER
    ; change the cursor position
    mov bh, 0   ; page no. 0
    mov dh, row ; what current row is
    mov dl, col ; what current col is
    mov ah, 02  ; service routine code for changing cursor
    int 10h     ; 10h/02 is the subroutine code of changing the cursor
    ; printing the blank character
    mov dl, blank_character
    mov ah, 02
    int 21h
    ret  ; so we don't have to jump so create the function

exit_program:
  ; exiting the program
  mov ah, 04ch
  int 21h

main endp
code_seg ends
end main
