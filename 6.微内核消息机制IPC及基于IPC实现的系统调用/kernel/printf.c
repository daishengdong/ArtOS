#include "type.h"
#include "const.h"
#include "protect.h"
#include "string.h"
#include "proc.h"
#include "tty.h"
#include "console.h"
#include "global.h"
#include "proto.h"
#include "keyboard.h"

int printf(const char *fmt, ...) {
    int i;
    char buf[256];

    va_list arg = (va_list)((char*)(&fmt) + 4); // 4 是参数 fmt 在堆栈中所占的大小

    i = vsprintf(buf, fmt, arg);
    buf[i] = 0;
    printx(buf);

    return i;
}
