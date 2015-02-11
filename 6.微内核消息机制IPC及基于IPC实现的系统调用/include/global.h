// 该文件定义了全局变量
// 在 global.c 中通过宏 GLOBAL_VARIABLES_HERE 的使用
// 在让所有变量只出现一次(在 global.h 中)的同时
// 预编译结束后, global.c 和其他 .c 文件中的结果不同
// 在 global.c 中变量前面没有 extern 关键字
// 而在其他文件中变量前面将会有 extern 关键字

// EXTERN is defined as extern except in global.c
#ifdef  GLOBAL_VARIABLES_HERE
#undef  EXTERN
#define EXTERN
#endif

EXTERN int                  ticks;

EXTERN int                  disp_pos;

EXTERN u8                   gdt_ptr[6];     // 0~15: Limit  16~47:Base
EXTERN struct descriptor    gdt[GDT_SIZE];
EXTERN u8                   idt_ptr[6];     // 0~15: Limit  16~47:Base
EXTERN struct gate          idt[IDT_SIZE];

EXTERN u32                  k_reenter;

EXTERN int                  nr_current_console;

EXTERN struct tss           tss;
// 就绪进程
EXTERN struct proc          *p_proc_ready;


// 在 global.c 中定义的进程表和任务栈
extern char                 task_stack[];
extern struct proc          proc_table[];
extern struct task          task_table[];
extern struct task          user_proc_table[];
extern irq_handler          irq_table[];
extern TTY                  tty_table[];
extern CONSOLE              console_table[];
