#include "headerLIST.h"

int main()
{
    struct list sp = {};
    int list_capacity = 5;

    ListCtor(&sp, list_capacity);

    Label l1 = 
    {
        l1.adr = 1;
        l1.name_of_adr = "next";
    };
    Label l2 = 
    {
        l2.adr = 2;
        l2.name_of_adr = "lol";
    };

    ListInsert(&sp, 0, l1);

    ListInsert(&sp, 0, l2);


    return 0;
}