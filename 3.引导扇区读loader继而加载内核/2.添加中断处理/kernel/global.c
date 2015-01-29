// 通过对 GLOBAL_VARIABLES_HERE 宏的定义
// 撤销全局变量前面的 extern 声明
// 这样只在这一个文件中定义了这些全局变量
// 其他文件里面都是全局变量的 extern 声明

#define GLOBAL_VARIABLES_HERE

#include "type.h"
#include "const.h"
#include "protect.h"
#include "proto.h"
#include "global.h"
