#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>
#include <math.h>

#include "headerASM_3.0.h"


#define LOX  printf("повезло повезло %d\n", __LINE__);       

typedef Label type_data;


void ListCtor(struct list * sp, int list_capacity);
void ListDtor(struct list* sp);
int ListInsert(struct list* sp, int log_num, int arg);
type_data ListDelete(list *sp, int index);
void ListDump(list* sp);
void ListFDump(list* sp);
int ListFoundNum(list * sp, int ph_num);
void ListSort(list * sp, list * sortsp);
void ListResize(list * sp); // defolt inc_koef = 2;

struct list
{
    type_data * data;
    int head;
    int tail;
    int capacity;
    int * next;
    int * prev;
    int free;
    int size;
};