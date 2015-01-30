// ------------------------------------------------------------------------
// 栈帧
typedef struct s_stackframe {
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
} STACK_FRAME;


// ------------------------------------------------------------------------
// PCB
typedef struct s_proc {
    STACK_FRAME regs;           // process registers saved in stack frame

    u16         ldt_sel;        // gdt selector giving ldt base and limit
    DESCRIPTOR  ldts[LDT_SIZE]; // local descriptors for code and data
    u32         pid;            // process id passed in from MM
    char        p_name[16];     // name of the process
} PROCESS;


// Numbers of tasks
// ArtOS 最大允许进程数
#define NR_TASKS    1

// stacks of tasks
#define STACK_SIZE_TESTA 0x8000

#define STACK_SIZE_TOTAL    STACK_SIZE_TESTA
