#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>
#include <math.h>

#define LOX printf("повезло повезло %d\n", __LINE__);

void StackCtor(struct Stack* stk, int capacity);

void StackPush(Stack* stk, double value);

double StackGet(Stack* stk);

void StackDtor(Stack* stk);

double StackPop(Stack* stk);

void StackUPsize(Stack* stk);

void StackDWsize(Stack* stk);

void StackDump(Stack* stk);

int StackVerify(Stack* stk);

void StackFDump(Stack* stk);

void ClearFile();

void StackClear(Stack* stk); //не корректно работает функция?

void StackOk(Stack* stk);

void DumpERrors(Stack* stk, FILE* fdump);

void CPUCtor(struct CPU* processor, int code_capacity);

struct Stack
{   
    long long canary1;
    double* data;
    int size;
    int capacity;
    long long canary2;
    int error_code;
};

struct CPU
{
    Stack stk;
    double registr[4];
    int* code;
    int code_capacity;
    int ip;
};

enum StackERrors
{
    STACK_OVERFLOW   = 1 << 1,
    SIZE_LESS_ZERO   = 1 << 2,
    CAP_LESS_ZERO    = 1 << 3,
    DATA_PTR_NULL    = 1 << 4,
    CANARY1_DIED     = 1 << 5,
    CANARY2_DIED     = 1 << 6,
    CANARY3_DIED     = 1 << 7,
    CANARY4_DIED     = 1 << 8,
};

#define DEF_CMD(name, num, arg, ...)                \
    CMD_ ## name = num,                              \


enum CMDS
{
    #include "enum.h"
};

#undef DEF_CMD

enum RegisterNum
{
    RAX = 1,
    RBX = 2,
    RCX = 3,
    RDX = 4,
};

