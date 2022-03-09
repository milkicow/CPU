#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>
#include <math.h>

#define LOX{                                   \
    printf("повезло повезло %d\n", __LINE__);   \
    fflush(stdout);                              \
}                                                 

enum CMDS
{
    CMD_PUSH  =  1,
    CMD_RPUSH = 11,
    CMD_MUL   =  2,
    CMD_POP   =  3,
    CMD_RPOP  = 33,
    CMD_ADD   =  4,
    CMD_SUB   =  5,
    CMD_OUT   =  6,
    CMD_DIV   =  7,
    CMD_SQRT  =  8,
    CMD_HLT   = -1,
    // (!) тестовый набор cmds (!) + добавить регистры и структуру CPU

};

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