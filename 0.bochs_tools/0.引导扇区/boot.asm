org 0x7c00
 
entry:
    mov ax, 0
    mov ss, ax
    mov sp, 0x7c00
    mov ds, ax
    mov es, ax

    mov si, message

print:
    mov al, [si]
    cmp al, 0
    je  fin
    mov ah, 0x0e
    mov bx, 15
    int 0x10
    inc si
    jmp print

fin:
    hlt
    jmp fin

message:
    db 0x0a, 0x0a
    db "hello, world"
    db 0x0a
    db 0

times 510 - ($ - $$)    db  0

; resb 510 - $
; resw 510 - $
; resd 510 - $
dw  0xaa55
; db  0x55, 0xaa
