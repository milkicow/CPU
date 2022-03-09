#include "headerLIST.h"

//-------------------------------------------------------------------------------------------------
//  отладка функций vv
//
// Осталось сделать:
//      добавить "подставляемый" дамп - для разных списков в одном вызове  
//      (не обязательно?) прочитать про сокращение структур на c++
//      работа не с датой а со структурой данных (поменять тип даты ??)
//-------------------------------------------------------------------------------------------------

void ListCtor(list* sp, int list_capacity)
{
    assert(sp);
    int min_list_capacity = 2;

    if(list_capacity < 2)
    {
        list_capacity = min_list_capacity;
    }

    sp -> data = (type_data *) calloc(list_capacity, sizeof(*(sp -> data)));
    assert(sp -> data);

    //sp -> data[0].adress = 0;

    for(int i = 0; i < NAME_LEN; i++)
    {
        sp -> data[0].name_of_adr[i] = 0;
    }

    sp -> next = (int *) calloc(list_capacity, sizeof(*(sp -> next)));
    assert(sp -> next); 

    sp -> next[0] = 0;

    for(int i = 1; i < list_capacity; i++)
    {
        sp -> next[i] = (-i - 1);
    }

    sp -> prev = (int *) calloc(list_capacity, sizeof(*(sp -> prev)));
    assert(sp -> prev);

    sp -> prev[0] = 0;

    for(int i = 1; i < list_capacity; i++)
    {
        sp -> prev[i] = -1;
    }


    sp -> capacity = list_capacity;
    sp -> free = 1;
    sp -> size = 0;

    sp -> head = 0;
    sp -> tail = 0;

}

void ListDtor(list* sp)
{   
    assert(sp);

    free(sp -> data);
    free(sp -> next);
    free(sp -> prev);
}

int ListInsert(list* sp, int index, type_data arg)
{   
    assert(sp);
    
    int ph_num = 0;
    int next_free = 0;

    if(sp -> size == 0)
    {   
        sp -> data[1] = arg;
        sp -> next[1] = 0;
        sp -> prev[1] = 0;

        sp -> head = sp -> free;
        sp -> tail = sp -> free;

        sp -> next[0] = sp -> head;
        sp -> prev[0] = sp -> tail;

        sp -> free = 2;

        ph_num = 1;

        sp -> size = 1;
    }
    else
    {
        if (sp -> size == sp -> capacity)
        {
            ListResize(sp);
        }

        next_free = - (sp -> next[sp -> free]);
        ph_num = sp -> free;

        sp -> next[sp -> free] = sp -> next[index];
        sp -> prev[sp -> next[index]] = sp -> free;

        sp -> next[index] = sp -> free;
        sp -> data[sp -> free] = arg;


        sp -> prev[sp -> free] = index;

        sp -> free = next_free;  
    }

    sp -> head = sp -> next[0];
    sp -> tail = sp -> prev[0];

    (sp -> size)++;

    return ph_num;
}

type_data ListDelete(list *sp, int index)
{   
    assert(sp);

    if(index == sp -> tail)
    {
        sp -> tail = sp -> prev[index];
    }   

    if(index == sp -> head)
    {
        sp -> head = sp -> next[index];
    }


    type_data delete_node = sp -> data[index];
    sp -> data[index].adr = 0;

    for(int i = 0; i < NAME_LEN; i++)
    {
        sp -> data[index].name_of_adr[i] = 0;
    }

    sp -> prev[sp -> next[index]] = sp -> prev[index];
    sp -> next[sp -> prev[index]] = sp -> next[index];

    sp -> prev[index] = -1;
    sp -> next[index] = -sp -> free;

    sp -> free = index;

    (sp -> size)--;

    return delete_node;

}

void ListDump(list* sp)
{
    for(int i = 0; i < sp -> capacity; i++)
    {   
        printf("data[%d] = %s \n", sp -> data[i].adr, sp -> data[i].name_of_adr); //
        printf("next[%d] = %d \n", i, sp -> next[i]);
        printf("prev[%d] = %d \n\n", i, sp -> prev[i]);
    }
    printf("free = %d\n", sp -> free);
    printf("head = %d\n", sp -> head);
    printf("tail = %d\n\n", sp -> tail);
    printf("size = %d", sp -> size);
 
}

void ListFDump(list* sp)
{
    FILE* fp = fopen("dump.txt", "w");
    assert(fp);

    fprintf(fp, "digraph G {\n");
    fprintf(fp, " rankdir=LR;\n");

    for(int i = 0; i < sp -> capacity; i++)
    {
        fprintf(fp, "node%d [shape=record,label=\"index %d | { data [%d] = %s | next %d | prev %d } \" ];\n", i, i, sp -> data[i].adr, sp -> data[i].name_of_adr, sp -> next[i], sp -> prev[i]); //
    }
    for(int i = 0; i < sp -> capacity - 1; i++)
    {
        fprintf(fp, "node%d -> node%d[color = transparent];\n", i, i + 1);
    }

    int last_index = 0;
    for(int i = 0; sp -> next[i] != 0; i = sp -> next[i])
    {
        fprintf(fp, "node%d -> node%d [color = pink];\n", i, sp -> next[i]);
        last_index = sp -> next[i];
    }   
    fprintf(fp, "node%d -> node0 [color = pink];\n", last_index);


    fprintf(fp, "info [shape=record, label =\"capacity %d | size %d | free %d \"];\n", sp -> capacity, sp -> size, sp -> free);

    fprintf(fp, "head [shape=box3d, label =\"head %d \"];\n", sp -> head);
    fprintf(fp, "tail [shape=box3d, label =\"tail %d \"];\n", sp -> tail);

    fprintf(fp, "head -> node%d;\n", sp -> head);
    fprintf(fp, "tail -> node%d;\n", sp -> tail);


    fprintf(fp, "}\n");
    fclose(fp);
    system("dot dump.txt -T pdf -o dump.pdf");
    system("open dump.pdf");
}

int ListFoundNum(list * sp, int index) // функция выдает логический номер элемента в списке 
{   
    char ans[5];

    printf("This function is far slower than \"Holin\", so\n");
    printf("Are u shure that u need to use this shit function?!\n");
    scanf("%s", ans);
    if (strcmp(ans, "yes") != 0)
    {   
        printf("pls try to do it in the other way\n");
        exit(EXIT_FAILURE);
    }

    printf("Are u idiot?!\n");
    scanf("%s", ans);
    if (strcmp(ans, "no") != 0)
    {
        printf("OK.\n");
        exit(EXIT_FAILURE);
    }

    int log_num = 0;
    for(int i = sp -> head; i != index; i = sp -> next[i])
    {
        log_num++;
        if(log_num > sp -> size)
        {
            printf("I can't find right index in this list!!!\n");
            printf("EXIT_FAILURE");
            exit(EXIT_FAILURE); 
        }
    }
    return log_num;
}

void ListSort(list * sp, list * sortsp) // функция сортирует первый аргумент - список таким образом, что индексы соотносятся с логическими номерами
{                                       // нужно вторым аргументом положить адрес куда будет помещен отсортированный список
    int j = 0;      

    for(int i = sp -> head; sp -> next[i] != sp -> head; i = sp -> next[i])
    {   
        ListInsert(sortsp, j, sp -> data[i]);

        j++;
    }
    sortsp -> head = sortsp -> next[0];
    sortsp -> tail = j;
}

void ListResize(list * sp)
{   
    assert(sp);

    int inc_koef = 2;
        
    sp -> data = (type_data *) realloc((int *) sp -> data, (inc_koef * sp -> capacity) * sizeof(*(sp -> data)));
    assert(sp -> data);

    sp -> next = (int *) realloc((int *) sp -> next, (inc_koef * sp -> capacity) * sizeof(*(sp -> next)));
    assert(sp -> next);

    sp -> prev = (int *) realloc((int *) sp -> prev, (inc_koef * sp -> capacity) * sizeof(*(sp -> prev)));
    assert(sp -> prev);


    for(int i = sp -> capacity; i < inc_koef * sp -> capacity; i++)
    {
        sp -> next[i] = (-i - 1);
    }
    for(int i = sp -> capacity; i < inc_koef * sp -> capacity; i++)
    {
        sp -> prev[i] = -1;
    }

    sp -> capacity = inc_koef * sp -> capacity;

}