[org 0x0100]

  ; since registers are 2 bytes, and out data (num) is a single byte, we can access only a single byte of register and add our value, and default 00 add in the other byte of register
  ; these two part of register are al, and ah, l and h for lower and higher respectively.

  ; now load it in ah, we can also do it in al
  mov ah, [num]
  mov bh, [num+1]

  add ah, bh

  mov bh, [num+2]
  add ah, bh

  mov [num+3], ah

  mov ax, 0x4c00 ; exit code ..
  int 0x21 ; .. is what the OS should do for me


; now we are not allocating the word (2 bytes), but a single byte
num: db 5, 10, 15, 0
