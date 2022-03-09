#include "headerCPU_3.0.h"

int main()
{   
    FILE* commands = NULL;
    commands = fopen("MachineFile.bin", "rb");
    assert(commands != NULL);

    CPU processor = {};

    int code_capacity = 0;
    fread(&code_capacity, 1, sizeof(int), commands);
    rewind(commands);


    CPUCtor(&processor, code_capacity);
    
    
    fread(processor.code, code_capacity, sizeof(int), commands);


    double value = 0;

    #define DEF_CMD(name, number, arg, ...)     \
                                                 \
    case CMD_ ## name:                            \
                                                   \
    __VA_ARGS__                                     \
                                                     \
    processor.ip++;                                   \
                                                       \
    break;                                              \


    while(processor.ip < code_capacity)
    {   

        switch (processor.code[processor.ip])
        {
            #include "enum.h"
            #undef DEF_CMD
        default:
            LOX;
            printf("ERror_CMD = %d\n", processor.code[processor.ip]);
            printf("ip = %d\n", processor.ip);


            StackDump(&(processor.stk));
            printf("\nPIZDA RULYAM\n");
            exit(EXIT_FAILURE);
            break;
        }
        /*if (processor.ip >= code_capacity) 
        {
            printf("BGCBCDip = %d", processor.ip);
        }
        else
        {
            printf("ip = %d code_capacity = %d", processor.ip, code_capacity);
        }*/
    }

    StackDump(&(processor.stk));

    StackDtor(&(processor.stk));

    free(processor.code);

    return 0;
}

void CPUCtor(struct CPU* processor, int code_capacity)
{
    StackCtor(&(processor -> stk), 1);

    for(int i = 0; i < 4; i++)
    {
        processor -> registr[i] = 0;
    }

    processor -> code_capacity = code_capacity;

    processor -> code = (int *) calloc(processor -> code_capacity, sizeof(int));

    processor -> ip = 1;

}