// 通过对 GLOBAL_VARIABLES_HERE 宏的定义
// 撤销全局变量前面的 extern 声明
// 这样只在这一个文件中定义了这些全局变量
// 其他文件里面都是全局变量的 extern 声明

#define GLOBAL_VARIABLES_HERE

#include "type.h"
#include "const.h"
#include "protect.h"
#include "string.h"
#include "proc.h"
#include "tty.h"
#include "console.h"
#include "global.h"
#include "proto.h"

// 进程表
// NR_TASKS 为 ArtOS 最大允许进程数
PUBLIC struct proc  proc_table[NR_TASKS + NR_PROCS];

// 任务的栈
PUBLIC char         task_stack[STACK_SIZE_TOTAL];

PUBLIC struct task  task_table[NR_TASKS] = {
    {task_tty,  STACK_SIZE_TTY,     "TTY"},
    {task_sys,  STACK_SIZE_SYS,     "SYS"},
};

PUBLIC struct task  user_proc_table[NR_PROCS] = {
    {TestA,     STACK_SIZE_TESTA,   "TestA"}, 
    {TestB,     STACK_SIZE_TESTB,   "TestB"}, 
    {TestC,     STACK_SIZE_TESTC,   "TestC"}, 
};

PUBLIC TTY          tty_table[NR_CONSOLES];
PUBLIC CONSOLE      console_table[NR_CONSOLES];

PUBLIC irq_handler  irq_table[NR_IRQ];

PUBLIC system_call  sys_call_table[NR_SYS_CALL] = {
    sys_printx,
    sys_sendrec,
};
