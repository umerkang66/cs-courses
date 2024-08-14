; There is a library (ld.so) that looks for the "start symbol"
; and executes from there. 

SECTION .text: ; for code
GLOBAL _start ; make the _start global, so that operating system can call it


_start: 
  ; writing a string to console
  mov eax, 0x4 ; write syscall
  mov ebx, 1 ; write in std output, there is a different code for file
  mov ecx, message
  mov edx, message_length
  int 0x80 ; invoke the system call

  ; exit the program
  mov eax, 0x1 ; exit system call
  mov ebx, 0 ; exit code 0 returned
  int 0x80 ; this interrupt is understandable by ubuntu


SECTION .data: ; VARIABLES SECTION
  message: db "Hello World!", 0xA, 0x0 ; 0xA is new_line_char, and 0x0 is null character
  message_length: equ $-message

; '$-message' means that the $ (current address) - address of message, since each character is stored in byte, this will calculate the total number of bytes, hence the length of string
