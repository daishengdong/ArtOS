#include "type.h"
#include "const.h"
#include "protect.h"
#include "string.h"
#include "proc.h"
#include "tty.h"
#include "console.h"
#include "global.h"
#include "proto.h"


// ----------------------------------------------------------------------------
// kernel_main 由内核跳入
PUBLIC int kernel_main() {
	disp_str("-----\"kernel_main\" begins-----\n");

    TASK    *p_task         = task_table;
    PROCESS *p_proc         = proc_table;
    char    *p_task_stack   = task_stack + STACK_SIZE_TOTAL;
    u16     selector_ldt    = SELECTOR_LDT_FIRST;
    int     i;
    u8      privilege;
    u8      rpl;
    int     eflags;
    for (i = 0; i < NR_TASKS + NR_PROCS; ++i) {
        if (i < NR_TASKS) {     // 任务
            p_task      = task_table + i;
            privilege   = PRIVILEGE_TASK;
            rpl         = RPL_TASK;
            eflags      = 0x1202;   // IF = 1, IOPL = 1, bit 2 is always 1
        } else {                // 用户进程
            p_task      = user_proc_table + (i - NR_TASKS);
            privilege   = PRIVILEGE_USER;
            rpl         = RPL_USER;
            eflags      = 0x202;   // IF = 1, IOPL = 1, bit 2 is always 1
        }
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
        p_proc->ldts[0].attr1 = DA_C | privilege << 5;
        memcpy(&p_proc->ldts[1], &gdt[SELECTOR_KERNEL_DS >> 3], sizeof(DESCRIPTOR));
        p_proc->ldts[1].attr1 = DA_DRW | privilege << 5;
        
        p_proc->regs.cs     = ((8 * 0) & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | rpl;
        p_proc->regs.ds     = ((8 * 1) & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | rpl;
        p_proc->regs.es     = ((8 * 1) & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | rpl;
        p_proc->regs.fs     = ((8 * 1) & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | rpl;
        p_proc->regs.ss     = ((8 * 1) & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | rpl;
        p_proc->regs.gs     = (SELECTOR_KERNEL_GS & SA_RPL_MASK) | rpl;

        p_proc->regs.eip    = (u32)p_task->initial_eip;
        p_proc->regs.esp    = (u32)p_task_stack;
        p_proc->regs.eflags = eflags;

        p_proc->nr_tty      = 0;

        p_task_stack        -= p_task->stacksize;
        ++p_proc;
        ++p_task;
        selector_ldt        += 1 << 3;
    }

	proc_table[0].ticks = proc_table[0].priority = 15;
	proc_table[1].ticks = proc_table[1].priority = 5;
	proc_table[2].ticks = proc_table[2].priority = 5;
	proc_table[3].ticks = proc_table[3].priority = 5;

    proc_table[1].nr_tty = 0;
    proc_table[2].nr_tty = 1;
    proc_table[3].nr_tty = 2;

    k_reenter           = 0;
    ticks               = 0;

    p_proc_ready        = proc_table;

    init_clock();
    init_keyboard();

    restart();

    while (1) {}
}


// ----------------------------------------------------------------------------
// TestA: 一个极简的"进程"
void TestA() {
    int i = 0;
    while (1) {
        printf("<Ticks:%x>", get_ticks());
        milli_delay(200);
    }
}


// ----------------------------------------------------------------------------
// TestB: 一个极简的"进程"
void TestB() {
    int i = 0x1000;
    while (1) {
        printf("B");
        milli_delay(200);
    }
}


// ----------------------------------------------------------------------------
// TestC: 一个极简的"进程"
void TestC() {
    int i = 0x2000;
    while (1) {
        printf("C");
        milli_delay(200);
    }
}
