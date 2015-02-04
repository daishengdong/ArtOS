#include "type.h"
#include "const.h"
#include "protect.h"
#include "proto.h"
#include "string.h"
#include "proc.h"
#include "global.h"


// ----------------------------------------------------------------------------
// 时钟中断处理函数
PUBLIC void clock_handler(int irq) {
    ++ticks;
    --p_proc_ready->ticks;

    if (k_reenter != 0)
        return;

    if (p_proc_ready->ticks > 0)
        return;

    schedule();
}


// ----------------------------------------------------------------------------
// 精确到 10ms 的延迟函数
PUBLIC void milli_delay(int milli_sec) {
    int t = get_ticks();
    while (((get_ticks() - t) * 1000 / HZ) < milli_sec) ;
}
