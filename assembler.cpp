#include "headerASM.h"

int SizeOfFile(FILE* fp);
void BufferText(FILE* fp, char*** lines, char** buffer, int size_of_file, int* nstr);
/*void AsmFDump(char** lines, char* buffer, int nstr);*/
void AsmFOut(char** lines, char* buffer, int nstr, int* code);
int SyntaxAnalysis(char* line);
int RegistrAnalysis(char* command);


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
    int  arg = 0;
    char rarg[10] = " ";
                                                  
                                            
    for(int i = 0; i < nstr; i++)
    {   
        if(sscanf(*lines, "%s", command) == 1)
        {

            if(strcmp(command, "push") == 0)
            {   
                if(SyntaxAnalysis(*lines) == NUMBER)
                {
                    sscanf(*lines, "%*s %d", &arg);

                    code[ip++] = CMD_PUSH;
                    code[ip++]   = arg;

                    fprintf(fdump, "push %d\n", arg);
                }
                else if(SyntaxAnalysis(*lines) == REGISTR)
                {   
                    sscanf(*lines, "%*s %s", rarg);

                    code[ip++] = CMD_RPUSH;
                    code[ip++] = RegistrAnalysis(rarg);

                    fprintf(fdump, "rpush %d\n", RegistrAnalysis(rarg));
                }
            }
            if(strcmp(command, "mul") == 0)
            {
                code[ip++] = CMD_MUL;

                fprintf(fdump, "mul\n");
            }
            if(strcmp(command, "pop") == 0)
            {   
                if(SyntaxAnalysis(*lines) == REGISTR)
                {   
                    sscanf(*lines, "%*s %s", rarg);

                    code[ip++] = CMD_RPOP;
                    code[ip++] = RegistrAnalysis(rarg);

                    fprintf(fdump, "rpop %d\n", RegistrAnalysis(rarg));
                }
                else 
                {
                    code[ip++] = CMD_POP;

                    fprintf(fdump, "pop\n");
                }
            }
            if(strcmp(command, "add") == 0)
            {
                code[ip++] = CMD_ADD;

                fprintf(fdump, "add\n");
            }
            if(strcmp(command, "sub") == 0)
            {
                code[ip++] = CMD_SUB;

                fprintf(fdump, "sub\n");
            }
            if(strcmp(command, "out") == 0)
            {
                code[ip++] = CMD_OUT;

                fprintf(fdump, "out\n");
            }
            if(strcmp(command, "div") == 0)
            {
                code[ip++] = CMD_DIV;

                fprintf(fdump, "div\n");
            }
            if(strcmp(command, "sqrt") == 0)
            {
                code[ip++] = CMD_SQRT;

                fprintf(fdump, "sqrt\n");
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


/*void AsmFDump(char** lines, char* buffer, int nstr) // убирать лишние пробелы до в строке и после нее
{   
    FILE* fdump = NULL;
    fdump = fopen("CheckFile.txt", "w");

    assert(fdump != NULL);

    for(int i = 0; i < nstr; i++)
    {

        fprintf(fdump, "%s\n", *(lines + i));
    }

    fclose(fdump);
}*/


/*void AsmFOut(char*** lines, char** buffer, int nstr) // кринжово сделано - каждая команда на новой строке - на разных строках с аргументом
{                                                    // спросить у Амадея как лучше сделать 
    FILE* out = NULL;
    out = fopen("MachineFile.txt", "w");

    assert(out != NULL);
    LOX;
    for(int i = 0; i < nstr; i++)
    {   
        LOX;
        if(strcmp(*(*lines), "push") == 0)
        {   
            (*lines)++;
            i++;

            fprintf(out, "%d%s", CMD_PUSH, **lines);
            LOX;
        }
        (*lines)++;
    }

    fclose(out);
}*/






// работает с условным словом push для одного аргумента vv

// если считывать в массив, то нужно выносить аргументы функций на отдельную строчку ??как??

//KEK при добавлении пробела в выводе - норм, иначе цифры в порядке возрастания upd: не вроде норм

//сделать список команд и их номера enum?
//выводить два файла - для проца и для проверки -> 

// большой if с командами и их номерами
// синхронизовать с тетрадью

