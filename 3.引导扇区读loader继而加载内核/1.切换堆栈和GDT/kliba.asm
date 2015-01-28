[section .data]
disp_pos dd  0

[section .text]

; 导出函数
global disp_str

; ------------------------------------------------------------------------
; 显示一个字符串
; 函数原型: disp_str(char *)
disp_str:
    push ebp
    mov ebp, esp

    mov esi, [ebp + 8]  ; pszInfo
    mov edi, [disp_pos]
	mov	ah, 0Fh			; 0000b: 黑底    1111b: 白字
.1:
    lodsb
    test al, al
    jz .2
    cmp al, 0Ah ; 是回车吗?
    jnz .3
    push eax
    mov eax, edi
    mov bl, 160
    div bl
    and eax, 0FFh
    inc eax
    mov bl, 160
    mul bl
    mov edi, eax
    pop eax
    jmp .1
.3:
    mov [gs:edi], ax
    add edi, 2
    jmp .1

.2:
    mov [disp_pos], edi

    pop ebp
    ret
