; ----------------------------------------------------------------------
; 编译连接方法:
; $ rm -f kernel.bin
; $ nasm -f elf -o kernel.o kernel.asm
; $ nasm -f elf -o string.o string.asm
; $ nasm -f elf -o klib.o klib.asm
; $ gcc -c -o start.o start.c
; $ ld -s -Ttext 0x30400 -o kernel.bin kernel.o string.o start.o kliba.o
; $ rm -f kernel.o string.o start.o

SELECTOR_KERNEL_CS  equ 8

; 导入函数
extern cstart

; 导入全局变量
extern gdt_ptr

[section .bss]
StackSpace  resb    2 * 1024
StackTop:           ; 栈顶

[section .text]     ; 代码在此
global _start       ; 导出 _start

_start:
    ; 把 esp 从 LOADER 挪到 KERNEL
    mov esp, StackTop           ; 堆栈在 bss 段中

    sgdt [gdt_ptr]              ; cstart() 中将会用到 gdt_ptr
    call cstart                 ; 在此函数中改变了 gdt_ptr, 让它指向新的 GDT
    lgdt [gdt_ptr]              ; 使用新的 GDT

    ; lidt [idt_ptr]

    jmp SELECTOR_KERNEL_CS:csinit
csinit:                         ; 这个跳转指令强制使用刚刚初始化的结构
    push 0
    popfd                       ; Pop top of stack into EFLAGS

    hlt
