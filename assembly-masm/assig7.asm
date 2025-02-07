.model small

data_seg segment 'data'
  input1 db 13,10,"Enter first number : $"
  input2 db 13,10,"Enter second number : $"
  st4 db 13,10,"What operation you want to perform (+ , - , * , / , &, | , ^) : $"
  st5 db 13,10,"The result is : $"
  minst db "-$"
  erromsg db 13,10,"Division by zero is not allowed $"
  first dw ?
  second dw ?
  totaldigits dw ?
  operation db ?
  result dw 0
  num dw 0,0,0,0,0,0,0
  number1 db 0,0,0
  number2 db 0,0,0

data_seg ends

stack_seg segment 'stack'
  dw 100 DUP(?)
stack_seg ends

code_seg segment 'code'
  assume cs:code_seg, ss:stack_seg, ds:data_seg

  main proc far
    mov ax, data_seg
    mov ds, ax
    mov dx, offset input1
    mov ah, 09h
    int 21h

    mov si, offset number1
    call read_number
    mov si, offset number1
    push totaldigits
    call convertnumber
    mov first, ax

    mov dx, offset input2
    mov ah, 09h
    int 21h

    mov si, offset number2
    call read_number
    mov si, offset number2
    push totaldigits
    call convertnumber
    mov second, ax

    call Additionpro

    mov dx, offset st4
    mov ah, 09h
    int 21h
    mov ah, 01h
    int 21h
    mov operation, al

    cmp operation, '+'
    je addsection
    cmp operation, '-'
    je subsection
    cmp operation, '*'
    je mulsection
    cmp operation, '/'
    je divsection
    cmp operation, '&'
    je Andsection
    cmp operation, '|'
    je Orsection
    cmp operation, '^'
    je Xorsection

    jmp endsection ; If user entered wrong command

  divsection:
    call Dividepro
    push result
    call printnumber
    jmp endsection

  addsection:
    call Additionpro
    push result
    call printnumber
    jmp endsection

  subsection:
    call Subtractionpro
    push result
    call printnumber
    jmp endsection

  mulsection:
    call Multiplypro
    push result
    call printnumber
    jmp endsection

  Orsection:
    call Orpro
    push result
    call printnumber
    jmp endsection

  Andsection:
    call Andpro
    push result
    call printnumber
    jmp endsection

  Xorsection:
    call Xorpro
    push result
    call printnumber
    jmp endsection

  endsection:
    mov ah, 4ch
    int 21h
  main endp

Multiplypro proc near
  xor dx, dx
  mov ax, first
  mov bx, second
  mul bx
  mov result, ax
  ret
Multiplypro endp

Dividepro proc near
  mov ax, first
  cmp ax, 0
  je div_error
  mov si, second
  cmp si, 0
  je div_error
  xor dx, dx
  div si
  mov result, ax
  jmp enddivproc

  div_error:
    mov dx, offset erromsg
    mov ah, 09h
    int 21h

  enddivproc:
    ret
Dividepro endp

Subtractionpro proc near
  mov ax, first
  sub ax, second
  mov result, ax
  ret
Subtractionpro endp

Additionpro proc near
  mov ax, first
  add ax, second
  mov result, ax
  ret
Additionpro endp

Orpro proc near
  mov ax, first
  mov bx, second
  or ax, bx
  mov result, ax
  ret
Orpro endp

Andpro proc near
  mov ax, first
  mov bx, second
  and ax, bx
  mov result, ax
  ret
Andpro endp

Xorpro proc near
  mov ax, first
  mov bx, second
  xor ax, bx
  mov result, ax
  ret
Xorpro endp

read_number proc near
  xor ax, ax
  mov cx, 0

  loopinput1:
    mov ah, 01h
    int 21h
    cmp al, 13         ; Check if Enter key is pressed
    je doneinput1
    sub al, '0'        ; Convert ASCII to numeric
    cmp al, 9
    ja invalid_input   ; Reject non-numeric input
    mov [si], al
    inc si
    inc cx
    cmp cx, 3
    jl loopinput1

  doneinput1:
    mov totaldigits, cx
    ret

  invalid_input:
    mov totaldigits, cx
    ret
read_number endp

convertnumber proc near
  xor ax, ax
  xor dx, dx
  mov bp, sp
  mov dx, [bp + 2]
  mov bl, 10
  mov cl, 100
  mov al, [si]
  cmp dx, 1
  je singledigit
  cmp dx, 2
  je twodigit

  mul cl
  mov dx, ax
  xor ax, ax
  inc si

  twodigit:
    mov al, [si]
    mul bl
    add dx, ax
    xor ax, ax
    inc si
    mov al, [si]
    CBW
    add ax, dx
    jmp endconvertproc

  singledigit:
    CBW

  endconvertproc:
    ret
convertnumber endp

printnumber proc near
  mov dx, offset st5
  mov ah, 09h
  int 21h

  mov bp, sp
  mov ax, [bp + 2]
  cmp ax, 0
  jge positive_number

  neg ax
  push ax
  mov dx, offset minst
  mov ah, 09h
  int 21h
  pop ax

  positive_number:
    cmp ax, 10
    jl printsingle
    mov bx, 10
    xor cx, cx
    mov si, offset num

  digit_extract:
    xor dx, dx
    div bx
    add dx, '0'
    mov [si], dx
    inc si
    inc cl
    cmp ax, 0
    jnz digit_extract

  print_digits:
    dec si
    mov dx, [si]
    mov ah, 02h
    int 21h
    dec cl
    cmp cl, 0
    jne print_digits
    jmp endprintproc

  printsingle:
    add ax, '0'
    mov dx, ax
    mov ah, 02h
    int 21h

  endprintproc:
    ret
printnumber endp

code_seg ends
end main
