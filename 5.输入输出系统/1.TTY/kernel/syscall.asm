%include "sconst.inc"

INT_VECTOR_SYS_CALL equ 0x90
_NR_get_ticks       equ 0       ; 要跟 global.c 中的 sys_call_table 的定义相对应
_NR_write           equ 1

; 导出符号
global get_ticks
global write

bits    32
[section .text]

; ------------------------------------------------------------------------
; 用户级的 get_ticks 系统调用
get_ticks:
    mov eax, _NR_get_ticks
    int INT_VECTOR_SYS_CALL
    ret

; ------------------------------------------------------------------------
; 用户级的 write 系统调用
; void write(char *buf, int len);
write:
    mov eax, _NR_write
    mov ebx, [esp + 4]
    mov ecx, [esp + 8]
    int INT_VECTOR_SYS_CALL
    ret
