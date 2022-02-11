#include <stdio.h>
extern int etext, edata, end;
int main()
{
    printf("etext为：%6lx。\n", (long)&etext);
    printf("edata为：%6lx。\n", (long)&edata);
    printf("end为：%6lx。\n", (long)&end);
    return 0;
}