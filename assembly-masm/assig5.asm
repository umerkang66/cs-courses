.model small

data_seg segment 'data'
  st1 db "Enter a 3 digit1 Num: $"
  st2 db 13, 10, "Enter a 3 digit2 Num: $"
  st3 db 13, 10, "Operation +, -, *, / : $"
  st4 db 13, 10, "Result: $"
  digit1hex db 0
  digit2hex db 0
  digit1 db 50 DUP (?)
  digit2 db 50 DUP (?)
  result db '000$'
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
  loop_body2:
    sub digit1[bx], 30h
    mov al, digit1[bx]
    mul dh
    add digit1hex, al
    mov al, dh
    mov dl, 10
    mul dl
    mov dh, al
    dec bx
    dec cx
    cmp cx, 0
    jg loop_body2
  
  ; now digit1hex has the 3 digit number in integer hex form

  mov ah, 09h
  mov dx, offset st2
  int 21h

  mov digit2[0], 4
  mov dx, offset digit2
  mov ah, 0ah
  int 21h
  mov bl, digit2[1]; bx = count
  mov bh, 00h
  mov digit2[bx+2], '$'

  ; convert three digit number into one number in register
  mov bx, 4
  mov dh, 1
  mov cx, 3
  loop_body:
    sub digit2[bx], 30h
    mov al, digit2[bx]
    mul dh
    add digit2hex, al
    mov al, dh
    mov dl, 10
    mul dl
    mov dh, al
    dec bx
    dec cx
    cmp cx, 0
    jg loop_body
  
  ; now digit2hex has the 3 digit number in integer hex form
  mov ah, 09h
  mov dx, offset st3
  int 21h

  mov ah, 01h
  int 21h
  mov operation, al

  cmp operation, '+'
  je plus_operation
  cmp operation, '-'
  je minus_operation
  cmp operation, '*'
  je multiply_operation
  cmp operation, '/'
  je divide_operation
  ; if none of the above
  jmp finish

  plus_operation:
    mov al, digit1hex  ; Load first number
    add al, digit2hex  ; Add second number
    mov bl, al         ; Save the result for further processing
    mov bh, 0
    push bx
    call display_decimal
    jmp finish
  minus_operation:
    mov al, digit1hex  ; Load first number
    sub al, digit2hex  ; Sub second number
    mov bl, al         ; Save the result for further processing
    mov bh, 0
    push bx
    call display_decimal
    jmp finish
  multiply_operation:
    mov al, digit1hex  ; Load first number
    mul digit2hex      ; Multiply second number
    push ax
    call display_decimal
    jmp finish
  divide_operation:
    mov ah, 00h
    mov al, digit1hex  ; Load first number
    div digit2hex      ; Divide second number, al has quotient, ah has remainder
    mov ah, 00h
    push ax
    call display_decimal
    jmp finish

  finish:
  mov ah, 04ch
  int 21h

main endp
  ; this receives 1 argument in stack means 2 bytes
display_decimal proc near 
  mov bp, sp
  mov ax, [bp + 2]

  ; Convert result (in BL) to decimal
  mov cx, 3          ; We expect 3 digits
  lea di, result+2   ; Point DI to the end of the result buffer (reserve space for 3 digits)
  convert_to_decimal:
  mov dx, 0      ; Clear DX for division
  mov dl, 10     ; Divisor is 10
  div dl         ; Divide AX by 10, quotient in AL, remainder in AH
  add ah, '0'    ; Convert remainder to ASCII
  mov [di], ah   ; Store ASCII digit
  dec di         ; Move to the previous digit position
  ; Set AX to quotient, al already has quotient
  mov ah, 00h
  loop convert_to_decimal ; Repeat for next digit

  ; Display the result
  lea dx, st4        ; Load "Result: " string
  mov ah, 09h
  int 21h

  lea dx, result     ; Point to the start of the result buffer
  mov ah, 09h
  int 21h
ret 2
display_decimal endp
code_seg ends

end main
