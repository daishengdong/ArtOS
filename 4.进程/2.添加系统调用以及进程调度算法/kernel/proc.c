#include "type.h"
#include "const.h"
#include "protect.h"
#include "proto.h"
#include "string.h"
#include "proc.h"
#include "global.h"


// ----------------------------------------------------------------------------
// 进程调度算法
PUBLIC void schedule() {
    PROCESS *p;
    int greatest_ticks  = 0;

    while (!greatest_ticks) {
        for (p = proc_table; p < proc_table + NR_TASKS; ++p) {
            if (p->ticks > greatest_ticks) {
                greatest_ticks  = p->ticks;
                p_proc_ready    = p;
            }
        }

        if (!greatest_ticks)
            for (p = proc_table; p < proc_table + NR_TASKS; ++p)
                p->ticks = p->priority;
    }
}

// ----------------------------------------------------------------------------
// get_ticks 系统调用的中断映射函数
PUBLIC int sys_get_ticks() {
    return ticks;
}
