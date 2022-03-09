#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>
#include <math.h>

#define LOX printf("повезло повезло %d\n", __LINE__);    

#define DEF_CMD(name, num, arg, ...)                \
    CMD_ ## name = num,                              \


enum CMDS
{
    #include "enum.h"
};

#undef DEF_CMD

enum ArgType
{
    NUMBER  = 1,
    REGISTR = 2,

};

enum RegisterNum
{
    RAX = 0,
    RBX = 1,
    RCX = 2,
    RDX = 3,
};