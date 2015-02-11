// ------------------------------------------------------------------------
// 栈帧
struct stackframe {
    // pushed by save()
    u32 gs;
    u32 fs;
    u32 es;
    u32 ds;
    u32 edi;
    u32 esi;
    u32 ebp;
    u32 kernel_esp; // popad will ignore it
    u32 ebx;
    u32 edx;
    u32 ecx;
    u32 eax;

    // return addr for kernel.asm::save()
    u32 retaddr;

    // pushed by CPU during interrupt
    u32 eip;
    u32 cs;
    u32 eflags;
    u32 esp;
    u32 ss;
};


// ------------------------------------------------------------------------
// PCB
struct proc {
    struct stackframe   regs;           // process registers saved in stack frame

    u16                 ldt_sel;        // gdt selector giving ldt base and limit
    struct descriptor   ldts[LDT_SIZE]; // local descriptors for code and data

    int                 ticks;          // remained ticks
    int                 priority;

    u32                 pid;            // process id passed in from MM
    char                name[16];     // name of the process

    int                 p_flags;        /**
                                         * process flags
                                         * A proc is runnable if p_flags == 0
                                         * 0: 进程正在运行或准备运行
                                         * SENDING: 进程处于发送消息的状态. 由于消息还未送达, 进程被阻塞.
                                         * RECEIVING: 进程处于接收消息的状态. 由于消息还未收到, 进程被阻塞.
                                         */

    MESSAGE             *p_msg;         // 指向消息体的指针
    int                 p_recvfrom;     // 假设进程 P 想要接收消息, 但目前没有进程发消息给它, 本成员记录 P 想要从谁那里接收消息
    int                 p_sendto;       // 假设进程 P 想要发送消息, 但目前没有进程接收它, 本成员记录 P 想要发送消息给谁

    int                 has_int_msg;    /**
                                         * nonzero if an INTERRUPT occurrend when
                                         * the task is not ready to deal with it
                                         * 如果有一个中断需要某进程来处理, 或者换句话说, 某进程正在等待一个中断发生——比如
                                         * 硬盘驱动可能会等待硬盘中断的发生, 系统在得知中断发生后会将此位置为 1
                                         */

    struct proc         *q_sending;     /**
                                         * queue of procs sending messages to
                                         * this proc
                                         * 如果由若干进程——比如 A, B, C 都向同一个进程 P 发送消息, 而 P 此时并未准备接收消息
                                         * 那么 A, B 和 C 将会排成一个队列.
                                         * 进程 P 的 q_sending 指向第一个试图发送消息的进程
                                         */
    struct proc         *next_sending;  /**
                                         * next proc in the sending
                                         * queue(q_sending)
                                         * 进程队列的 next 指针
                                         */

    int                 nr_tty;         // 当前进程运行的 tty
};


// ------------------------------------------------------------------------
// TASK
struct task {
    task_f  initial_eip;
    int     stacksize;
    char    name[32];
};


#define proc2pid(x) (x - proc_table)

// Numbers of tasks & procs
// ArtOS 最大允许任务和进程数
#define NR_TASKS    2
#define NR_PROCS    3
#define FIRST_PROC  proc_table[0]
#define LAST_PROC   proc_table[NR_TASKS + NR_PROCS - 1]

// stacks of tasks
#define STACK_SIZE_TTY      0x8000
#define STACK_SIZE_SYS      0x8000
#define STACK_SIZE_TESTA    0x8000
#define STACK_SIZE_TESTB    0x8000
#define STACK_SIZE_TESTC    0x8000

#define STACK_SIZE_TOTAL    (STACK_SIZE_TTY + \
                            STACK_SIZE_SYS + \
                            STACK_SIZE_TESTA + \
                            STACK_SIZE_TESTB + \
                            STACK_SIZE_TESTC)
