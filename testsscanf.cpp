#include <stdio.h>

int main()
{
    char str1[20] = "push 5";
    char str2[20] = "fff";
    int d = 0;
   

    d = sscanf(str1, "%*s %s", str2); // считывает в str2 строку из str1

    printf("%s\n", str1);
    printf("%s\n", str2);

    printf("d = %d", d);


    return 0;
}