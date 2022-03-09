#include "headerASM_3.0.h"

int SizeOfFile(FILE* fp);
void BufferText(FILE* fp, char*** lines, char** buffer, int size_of_file, int* nstr);
/*void AsmFDump(char** lines, char* buffer, int nstr);*/
void AsmFOut(char** lines, char* buffer, int nstr, int* code);
int SyntaxAnalysis(char* line);
int RegistrAnalysis(char* command);
Label FindLabel();


int main()
{
    FILE* fp = NULL;
    FILE* out = NULL;

    fp = fopen("assembler.txt", "r");
    out = fopen("MachineFile.bin", "wb");

    assert(fp != NULL);
    assert(out != NULL);

    char** lines  = nullptr;
    char* buffer = nullptr;

    int nstr = 1;
    

    BufferText(fp, &lines, &buffer, SizeOfFile(fp), &nstr);

    int MAX_LEN_CODE = nstr * 2;
    int code[MAX_LEN_CODE];


    AsmFOut(lines, buffer, nstr, code);

    fwrite(code, code[0], sizeof(code[0]), out);

    fclose(fp);
    fclose(out);
    
    return 0;
}


int SizeOfFile(FILE* fp)
{   
    assert(fp);

    fseek(fp, 0L, SEEK_END);
    int size  = ftell(fp);

    rewind(fp);
    return size;
}

void BufferText(FILE* fp, char*** lines, char** buffer, int size_of_file, int* nstr) //функция в которой лучше не разбираться !!!
{                                                                                   // buffer - указатель на указатель на массив буфера                                                                 // lines - указатель на указатель на массив указателей на строки в массиве буфер
    assert(fp);                                                                     // добавить пропуск большого количества пробелов - смотреть Онегина
    assert(size_of_file);                                                           // не работает с большим количеством пробелов
    assert(lines);
    assert(buffer);

    *buffer = (char*) calloc(size_of_file + 1, sizeof(char));
    fread(*buffer, sizeof(char), size_of_file, fp);



    for(int i = 0; i < size_of_file; i++)
    {   
        if(*(*buffer + i) == '\n') // *(buffer[i]) // buffer[i] == *(buffer + i)
        {  
            (*nstr)++;
        }

    }

    *lines = (char**) calloc(*nstr + 1, sizeof(char*));
    assert(lines);

    char** start = *lines;

    **lines = *buffer;
    (*lines)++;

    for(int i = 0; i < size_of_file; i++)
    {
        if(*(*buffer + i) == '\n')
        {   
            *(*buffer + i) = '\0';
            *(*lines) = (*buffer + i) + 1;// **lines = *buffer + i + 1;
            (*lines)++;//
        }

    }
    *lines = start;

}

void AsmFOut(char** lines, char* buffer, int nstr, int* code)
{
    FILE* outtxt = NULL;
    FILE* fdump = NULL;

    outtxt = fopen("MachineFile.txt", "w");
    fdump = fopen("CheckFile.txt", "w");


    int ip = 1;

    char command[5];
    int  argument = 0;
    char rarg[10] = " ";

    #define DEF_CMD(name, num, arg, ...)        \
                                                 \
    if(strcmp(command, #name) == 0)               \
    {                                              \
        if(arg == 0)                                \
        {                                            \
            code[ip++] = CMD_ ## name;                \
                                                       \
            fprintf(fdump, #name"\n");                  \
        }                                                \
        else if(arg == 1)                                 \
        {                                                  \
            if(SyntaxAnalysis(*lines) == NUMBER)            \
            {                                                \
                sscanf(*lines, "%*s %d", &argument);          \
                                                               \
                    code[ip++] = CMD_ ## name;                  \
                    code[ip++]   = argument;                     \
                                                                  \
                    fprintf(fdump, #name " %d \n", argument);      \
                                                                    \
            }                                                        \
            else if(SyntaxAnalysis(*lines) == REGISTR)                \
            {                                                          \
                sscanf(*lines, "%*s %s", rarg);                         \
                                                                         \
                    code[ip++] = CMD_ ## name + 1;                        \
                    code[ip++] = RegistrAnalysis(rarg);                    \
                                                                            \
                    fprintf(fdump, #name " %d\n", RegistrAnalysis(rarg));    \
                                                                              \
            }                                                                  \
        }                                                                       \
    }                                                                            \
    else                                                                          \
    /*
    struct Label* labels;
    
    #define DEF_JUMP(name, num, condition)              \
                                                         \
    if(strcmp(command, #name) == 0)                       \
    {                                                      \
        struct Label label = FindLabel(labels);             \
        code[ip++] = JMP_ ## name;                           \
        code[ip++] = label.pointer;                           \
        fprintf(fdump, #name" %s\n", label.name_of_adr);       \
    }                                                           \
    else                                                         \
    */





    for(int i = 0; i < nstr; i++)
    {   
        if(sscanf(*lines, "%s", command) == 1)
        {
            #include "enum.h"
            #undef DEF_CMD
            {
                printf("undentified command found\n");
                exit(EXIT_FAILURE);
            }
        }
        (lines)++;
    }

    code[0] = ip;

    for(int i = 0; i < ip; i++)
    {
        fprintf(outtxt, "%d ", code[i]);
        printf("%d ", code[i]);
    }
}

int SyntaxAnalysis(char* line)
{   
    int number = 0;
    char readline[10] = " ";

    if(sscanf(line, "%*s %d", &number) == 1)
    {
        return NUMBER;
    }
    else if(sscanf(line, "%*s %s", readline) == 1)
    {   
        return REGISTR;
    }
    else
    {
        puts(line);
        puts("SyntaxAnalysisERror\n");
        exit(EXIT_FAILURE);
    }
}

int RegistrAnalysis(char* command)
{
    if (strcmp(command, "rax") == 0)
    {
        return RAX;
    }
    else if (strcmp(command, "rbx") == 0)
    {
        return RBX;
    }
    else if (strcmp(command, "rcx") == 0)
    {
        return RCX;
    }
    else if (strcmp(command, "rdx") == 0)
    {
        return RDX;
    }
    else 
    {
        puts("unrecognized registr read");
        exit(EXIT_FAILURE);
    }
}

Label FindLabel(Label* labels)
{  
    

}