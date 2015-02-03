#include "type.h"
#include "const.h"
#include "protect.h"
#include "proto.h"
#include "string.h"
#include "proc.h"
#include "global.h"

// ----------------------------------------------------------------------------
// kernel_main 由内核跳入
PUBLIC int kernel_main() {
	disp_str("-----\"kernel_main\" begins-----\n");

    TASK    *p_task         = task_table;
    PROCESS *p_proc         = proc_table;
    char    *p_task_stack   = task_stack + STACK_SIZE_TOTAL;
    u16     selector_ldt    = SELECTOR_LDT_FIRST;

    int i;
    for (i = 0; i < NR_TASKS; ++i) {
        // name of the process
        strcpy(p_proc->p_name, p_task->name);
        // pid
        p_proc->pid = i;

        p_proc->ldt_sel = selector_ldt;

        // 由 8 的倍数的偏移变成数组的下标
        // 进程的两个 ldt 为了简化起见, 分别被初始化位内核代码段和内核数据段
        // 只是改变了以下 DPL 以让其运行在低特权级下
        memcpy(&p_proc->ldts[0], &gdt[SELECTOR_KERNEL_CS >> 3], sizeof(DESCRIPTOR));
        // chage the DPL
        p_proc->ldts[0].attr1 = DA_C | PRIVILEGE_TASK << 5;
        memcpy(&p_proc->ldts[1], &gdt[SELECTOR_KERNEL_DS >> 3], sizeof(DESCRIPTOR));
        p_proc->ldts[1].attr1 = DA_DRW | PRIVILEGE_TASK << 5;
        
        p_proc->regs.cs     = ((8 * 0) & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | RPL_TASK;
        p_proc->regs.ds     = ((8 * 1) & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | RPL_TASK;
        p_proc->regs.es     = ((8 * 1) & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | RPL_TASK;
        p_proc->regs.fs     = ((8 * 1) & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | RPL_TASK;
        p_proc->regs.ss     = ((8 * 1) & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | RPL_TASK;
        p_proc->regs.gs     = (SELECTOR_KERNEL_GS & SA_RPL_MASK) | RPL_TASK;

        p_proc->regs.eip    = (u32)p_task->initial_eip;
        p_proc->regs.esp    = (u32)p_task_stack;
        p_proc->regs.eflags = 0x1202;   // IF = 1, IOPL = 1, bit 2 is always 1

        p_task_stack        -= p_task->stacksize;
        ++p_proc;
        ++p_task;
        selector_ldt        += 1 << 3;
    }

    k_reenter           = 0;

    p_proc_ready        = proc_table;

    put_irq_handler(CLOCK_IRQ, clock_handler);  // 设定时钟中断处理程序
    enable_irq(CLOCK_IRQ);                      // 让8259A可以接收时钟中断

    restart();

    while (1) {}
}


// ----------------------------------------------------------------------------
// TestA: 一个极简的"进程"
void TestA() {
    int i = 0;
    while (1) {
        disp_str("A");
        disp_int(++i);
        disp_str(".");
        delay(1);
    }
}


// ----------------------------------------------------------------------------
// TestB: 一个极简的"进程"
void TestB() {
    int i = 0x1000;
    while (1) {
        disp_str("B");
        disp_int(++i);
        disp_str(".");
        delay(1);
    }
}


// ----------------------------------------------------------------------------
// TestC: 一个极简的"进程"
void TestC() {
    int i = 0x2000;
    while (1) {
        disp_str("C");
        disp_int(++i);
        disp_str(".");
        delay(1);
    }
}
