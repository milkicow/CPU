#include "headerCPU_2.0.h"

/*
if (error)
    status |= error_code;

000100101
|
110011110
=
110111111
*/



void StackCtor(struct Stack* stk, int capacity)
{
    assert(stk);

    stk -> error_code = 0;

    stk -> data = (double*) calloc(capacity + 2, sizeof(*(stk -> data))); //незанятая память переделать немного каллок vv
    if(stk -> data == NULL) stk -> error_code |= DATA_PTR_NULL;           // подвинуть дату - массив с 0 элементами - подвинуть при освоблождении - при диструкторе 

    stk -> capacity = capacity;
    if(stk -> capacity <= 0) stk -> error_code |= CAP_LESS_ZERO;

    stk -> size = 0; 

    stk -> canary1 = 0xBE31AB;
    stk -> canary2 = 0xBE31AB;

    *(long long*)(stk -> data) = 0xBE31AB;

    stk -> data++;

    *(long long*)((char*)stk -> data + sizeof(*(stk -> data)) * (stk -> capacity)) = 0xBE31AB;


}
// Разобраться полностью со структурами!!! vv

void StackPush(Stack* stk, double value)
{   
    assert(stk);
    StackOk(stk);

    if ((stk -> size) >= (stk -> capacity))
    {   
        StackUPsize(stk);
    }

    stk -> data[stk -> size++] = value;
    StackOk(stk);
}

double StackGet(Stack* stk)
{
    return (stk -> data[stk -> size - 1]);
}

void StackDtor(Stack* stk)
{
    assert(stk);

    stk -> canary1 = 0;
    stk -> canary2 = 0;

    free(stk -> data - 1);
}

double StackPop(Stack* stk)
{
    assert(stk);
    StackOk(stk);

    if((4 * stk -> capacity) > (10 * stk -> size))
    {
        StackDWsize(stk);
    }

    /*if(stk -> size <= 0)
    {
        //печатать ошибку ?
        stk -> size = ERRPTR; - создать enum и выводить коды ошибок -> нужно будет убрать assert // прочитать про enum
    }*/
    double value = 0;

    value = stk -> data[--stk -> size];

    stk -> data[stk -> size] = 0;
    StackOk(stk);

    return(value);
}

void StackClear(Stack* stk)
{
    for(int i = 0; i < stk -> size; i++)
    {
        stk -> data[i] = 0;
        
    }
    stk -> size = 0;

}

void StackUPsize(Stack* stk)
{   
    assert(stk);
    StackOk(stk);

    *(int*)((char*)stk -> data + sizeof(*(stk -> data)) * (stk -> capacity)) = 0;

    stk -> data = (double*) realloc((double*) stk -> data - 1, (2 * stk -> capacity + 2) * sizeof(*(stk -> data)));
    stk -> capacity = 2 * stk -> capacity;
    stk -> data++;
 
    *(int*)((char*)stk -> data + sizeof(*(stk -> data)) * (stk -> capacity)) = 0xBE31AB;

    StackOk(stk);
}


void StackDWsize(Stack* stk)
{
    assert(stk);
    StackOk(stk);

    *(int*)((char*)stk -> data + sizeof(*(stk -> data)) * (stk -> capacity)) = 0;

    stk -> data = (double*) realloc((double*) stk -> data - 1, (0.5 * stk -> capacity + 2) * sizeof(*(stk -> data)));
    stk -> capacity = stk -> capacity * 0.5;
    stk -> data++;
     
    *(int*)((char*)stk -> data + sizeof(*(stk -> data)) * (stk -> capacity)) = 0xBE31AB;

}

void StackDump(Stack* stk)
{   
    assert(stk);

    printf("\n------------------------------------------\n");

    printf("canary1 = %llX\n", stk -> canary1);
    printf("canary2 = %llX\n", stk -> canary2);

    printf("data = %p\n", stk -> data);
    printf("size = %d\n", stk -> size);
    printf("capacity = %d\n\n", stk -> capacity);

    printf("canary3 = %X\n", *(int*)(stk -> data - 1)); //поправить !!! с датой - сместили на начало массива v
    for(int i = 0; i < (stk -> size); i++)
    {   
        printf("*[%d] = %.2lf\n", i, stk -> data[i]);
    }

    for(int i = stk -> size; i < (stk -> capacity); i++)
    {   
        printf(" [%d] = %.2lf\n", i, stk -> data[i]);
    }
    printf("canary4 = %X\n", *(int*)((char*)stk -> data + sizeof(*(stk -> data)) * (stk -> capacity)));
    printf("------------------------------------------\n");
}

void StackFDump(Stack* stk)
{   
    assert(stk);

    FILE* fdump = NULL;
    fdump = fopen("FDUMP.txt", "a");


    fprintf(fdump, "\n------------------------------------------\n");

    DumpERrors(stk, fdump);

    fprintf(fdump, "ERror_status = %d\n", stk -> error_code);

    fprintf(fdump, "canary1 = %llX\n", stk -> canary1);
    fprintf(fdump, "canary2 = %llX\n", stk -> canary2);

    fprintf(fdump, "data = %p\n", stk -> data);
    fprintf(fdump, "size = %d\n", stk -> size);
    fprintf(fdump, "capacity = %d\n\n", stk -> capacity);


    fprintf(fdump, "canary3 = %X\n", *(int*)(stk -> data - 1));
    for(int i = 0; i < (stk -> size); i++)
    {   
        fprintf(fdump, "*[%d] = %.2lf\n", i, stk -> data[i]);
    }

    for(int i = stk -> size; i < (stk -> capacity); i++)
    {   
        fprintf(fdump, " [%d] = %.2lf\n", i, stk -> data[i]);
    }
    fprintf(fdump, "canary4 = %X\n", *(int*)((char*)stk -> data + sizeof(*(stk -> data)) * (stk -> capacity)));
    fprintf(fdump, "------------------------------------------\n");

    fclose(fdump);
}

void ClearFile()
{
    FILE* fdump  = NULL;
    fdump = fopen("FDUMP.txt", "w");
    fclose(fdump);
}

int StackVerify(Stack* stk)
{
    if(stk -> canary1 != 0xBE31AB)       stk -> error_code |= CANARY1_DIED;
    if(stk -> canary2 != 0xBE31AB)       stk -> error_code |= CANARY2_DIED;
    if(stk -> data == NULL)              stk -> error_code |= DATA_PTR_NULL;
    if(stk -> size < 0)                  stk -> error_code |= SIZE_LESS_ZERO;
    if(stk -> capacity < 0)              stk -> error_code |= CAP_LESS_ZERO;
    if(stk -> size > stk -> capacity)    stk -> error_code |= STACK_OVERFLOW;
    if(*(int*)(stk -> data - 1) != 0xBE31AB) stk -> error_code |= CANARY3_DIED;
    if(*(int*)((char*)stk -> data + sizeof(*(stk -> data)) * (stk -> capacity)) != 0xBE31AB) stk -> error_code |= CANARY4_DIED;

    return(stk -> error_code);
}

void StackOk(Stack* stk)
{
    if (StackVerify(stk))
    {
        StackDump(stk);
        printf("VI GOVNO ** STEK GENIY");
        exit(EXIT_FAILURE);
    }
}

// проверить с каким сайзом я попаю - начиная с <0 или с 0

void DumpERrors(Stack* stk, FILE* fdump)
{
    if(stk -> error_code & STACK_OVERFLOW)
    {
        fprintf(fdump, "STACK_OVERFLOW\n");
    }
    if(stk -> error_code & SIZE_LESS_ZERO)
    {
        fprintf(fdump, "SIZE_LESS_ZERO\n");
    }
    if(stk -> error_code & CAP_LESS_ZERO)
    {
        fprintf(fdump, "CAP_LESS_ZERO\n");
    }
    if(stk -> error_code & DATA_PTR_NULL)
    {
        fprintf(fdump, "DATA_PTR_NULL\n");
    }
    if(stk -> error_code & CANARY1_DIED)
    {
        fprintf(fdump, "CANARY1_DIED\n");
    }
    if(stk -> error_code & CANARY2_DIED)
    {
        fprintf(fdump, "CANARY2_DIED\n");
    }
    if(stk -> error_code & CANARY3_DIED)
    {
        fprintf(fdump, "CANARY3_DIED\n");
    }
    if(stk -> error_code & CANARY4_DIED)
    {
        fprintf(fdump, "CANARY4_DIED\n");
    }
}




//плохо работает realloc
//...
//очень плохо // оказалось, что изменение памяти плохо работает YA_YBLAN там было указано в байтах -> надо было умножить еще на sizeof

// прочитать еще раз про realloc действительно vv



// написать dump - вывод данных о стеке vv

// прочитать про size_t vv
// прочитать про typedef vv
// прочитать про realloc  vv
// прочитать про enum vv


// StackOK() !!

// канарейки !!

// хэш !!