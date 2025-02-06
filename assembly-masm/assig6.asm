.model small

data_seg segment 'data'
  num dw 25, 11, 22, 30, 09
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
  dec cx ; outer loop runs n-1 times
  outer_loop:
    mov bx, 0 ; reset index for each outer loop iteration
    inner_loop:
      mov ax, num[bx]   ; load current element
      mov dx, num[bx+2] ; load next element
      cmp ax, dx
      jle no_swap       ; if ax <= dx, no swap needed
      ; swap elements
      mov num[bx], dx
      mov num[bx+2], ax
      no_swap:
      add bx, 2         ; move to next pair of elements
      cmp bx, 8         ; because we are checking bx+2, so stop before -2
      jl inner_loop     
    loop outer_loop

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
