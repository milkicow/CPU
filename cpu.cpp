#include "headerCPU.h"

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


    while(processor.ip < code_capacity)
    {   

        switch (processor.code[processor.ip])
        {
        case CMD_PUSH:

            LOX;

            StackPush(&(processor.stk), processor.code[++processor.ip]);
            processor.ip++;


            break;

        case CMD_RPUSH: //из регистра в стек
            LOX;

            StackPush(&(processor.stk), processor.registr[processor.code[++processor.ip]]);
            processor.ip++;

            break;

        case CMD_MUL:
            StackPush(&(processor.stk), StackPop(&(processor.stk)) * StackPop(&(processor.stk)));
            processor.ip++;

            break;
        
        case CMD_POP:
            LOX;

            StackPop(&(processor.stk));
            processor.ip++;

            break;

        case CMD_RPOP: // из стека в регистр

            processor.registr[processor.code[++processor.ip]] = StackPop(&(processor.stk));
            
            processor.ip++;

            break;
            
        case CMD_ADD:
            LOX;
            value = StackPop(&(processor.stk));
            StackPush(&(processor.stk), value + StackPop(&(processor.stk)));
            processor.ip++;

            break; 

        case CMD_SUB:
            LOX;
            value = StackPop(&(processor.stk));
            StackPush(&(processor.stk), StackPop(&(processor.stk)) - value);
            processor.ip++;

            break;

        case CMD_OUT:
            LOX;
            value = StackPop(&(processor.stk));

            printf("%lf", value);
            processor.ip++;

            break;

        case CMD_DIV:
            LOX;
            value = StackPop(&(processor.stk));
            StackPush(&(processor.stk), StackPop(&(processor.stk)) / value);
            processor.ip++;

            break; 

        case CMD_SQRT:
            LOX;
            StackPush(&(processor.stk), sqrt(StackPop(&(processor.stk))));
            processor.ip++;

            break;

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
