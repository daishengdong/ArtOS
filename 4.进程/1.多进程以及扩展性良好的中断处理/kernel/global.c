// 通过对 GLOBAL_VARIABLES_HERE 宏的定义
// 撤销全局变量前面的 extern 声明
// 这样只在这一个文件中定义了这些全局变量
// 其他文件里面都是全局变量的 extern 声明

#define GLOBAL_VARIABLES_HERE

#include "type.h"
#include "const.h"
#include "protect.h"
#include "proto.h"
#include "proc.h"
#include "global.h"

// 进程表
// NR_TASKS 为 ArtOS 最大允许进程数
PUBLIC PROCESS proc_table[NR_TASKS];

// 任务的栈
PUBLIC char     task_stack[STACK_SIZE_TOTAL];

PUBLIC TASK     task_table[NR_TASKS] = {
    {TestA, STACK_SIZE_TESTA, "TestA"}, 
    {TestB, STACK_SIZE_TESTB, "TestB"}, 
    {TestC, STACK_SIZE_TESTC, "TestC"}, 
};

PUBLIC  irq_handler irq_table[NR_IRQ];
