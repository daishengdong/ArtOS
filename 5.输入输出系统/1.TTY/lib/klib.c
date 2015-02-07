#include "type.h"
#include "const.h"
#include "protect.h"
#include "string.h"
#include "proc.h"
#include "tty.h"
#include "console.h"
#include "global.h"
#include "proto.h"


// ------------------------------------------------------------------------
// 仿 itoa
// 数字前面的 0 不被显示出来, 比如 000B800 被显示成 B800
PUBLIC char *itoa(char *str, int num) {
    char    *p = str;
    char    ch;
    int     i;
    // flag 用来标识第一个非 0 的数
    int     flag = 0;

    *p++ = '0';
    *p++ = 'x';
    if (num == 0) *p++ = '0';
    else {
        for (i = 28; i >= 0; i -= 4) {
            ch = (num >> i) & 0xF;
            if (flag || (ch > 0)) {
                flag = 1;
                ch += '0';
                if (ch > '9') ch += 7;
                *p++ = ch;
            }
        }
    }
    *p = 0;
    return str;
}


// ------------------------------------------------------------------------
// 以 16 进制形式打印数字
PUBLIC void disp_int(int input) {
    char output[16];
    itoa(output, input);
    disp_str(output);
}


// ------------------------------------------------------------------------
// 用循环实现延迟
PUBLIC void delay(int time) {
    int i, j, k;
    for (k = 0; k < time; ++k)
        for (i = 0; i < 100; ++i)
            for (j = 0; j < 10000; ++j)
                ;
}
