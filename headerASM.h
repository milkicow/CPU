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

#define DEF_JMP(name, num, conditions)              \
    CMD_ ## name = num,                              \

enum CMDS
{
    #include "commands.h"
};

#undef DEF_CMD
#undef DEF_JMP

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

const int NAME_LEN = 10;

struct Label
{
    int adr;
    char name_of_adr[NAME_LEN];
};
