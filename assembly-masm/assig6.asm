.model small

data_seg segment 'data'
  num dw 1, 5, 2, 4, 3
  counter dw 0
  inner_counter dw 2
  newline db 10, 13, '$'
data_seg ends

stack_seg segment 'stack'
  dw 100 DUP(?)
stack_seg ends

code_seg segment 'code'
  assume cs:code_seg, ds:data_seg, ss:stack_seg
main proc far
  mov ax, data_seg
  mov ds, ax

  ; printing the initial value
  mov ax, offset num
  mov cx, 5
  push ax
  push cx
  call print

  ; ACTUAL BUBBLE SORT LOGIC
  mov cx, 5
  outer_loop: 
    mov ax, counter
    add ax, 2
    mov inner_counter, ax
    push cx
    dec cx  ; inner loop should n-1 times

    inner_loop:
      mov bx, counter
      mov ax, num[bx]

      mov bx, inner_counter
      mov dx, num[bx]

      cmp ax, dx
      jle end_inner
      ; swapping logic here
      mov si, counter
      mov ax, num[si] ; first value

      mov di, inner_counter
      mov dx, num[di] ; second value

      mov num[si], dx
      mov num[di], ax

      end_inner:
      add inner_counter, 2
      dec cx
      cmp cx, 0
      jne inner_loop

    add counter, 2
    pop cx
    dec cx
    cmp cx, 0
    jne outer_loop

    ; printing the result
    mov ax, offset num
    mov cx, 5
    push ax
    push cx
    call print
  
  ; exit the program
  mov ah, 04ch
  int 21h
main endp
; two arguments: 1) offset address of first element 2) total no. of elements
print proc near
  mov ax, data_seg
  mov ds, ax

  mov bp, sp
  mov cx, [bp + 2] ; length of array
  mov bx, [bp + 4] ; offset address of first element
  loop_body: 
    mov ax, [bx]   
    aam
    add ax, 3030h
    push ax
    mov dl, ah
    mov ah, 02h
    int 21h
    pop ax
    mov dl, al
    mov ah, 02h
    int 21h
    mov ah, 02h
    mov dl, ' '
    int 21h
    add bx, 2
    loop loop_body
  mov dx, offset newline
  mov ah, 09h
  int 21h
  ret 4
print endp
code_seg ends

; starting point of the program
end main
