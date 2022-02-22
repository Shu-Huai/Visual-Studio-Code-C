#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define SHW_ADR(ID, I) printf("%s的地址：%8lX。\n", ID, (long)&I);
extern int etext, edata, end;
char buffer1[25];
char *cptr = "测试。\n";
void Function(char *p)
{
    char *buffer2;
    SHW_ADR("buffer2", buffer2);
    if ((buffer2 = (char *)malloc((unsigned)(strlen(p) + 1))))
    {
        strcpy(buffer2, p);
        printf("%s", buffer2);
        free(buffer2);
    }
    else
    {
        printf("Allocation error.\n");
        exit(1);
    }
}
int main()
{
    void Function(char *);
    printf("etext为：%6lx。\n", (long)&etext);
    printf("edata为：%6lx。\n", (long)&edata);
    printf("end为：%6lx。\n", (long)&end);
    SHW_ADR("main", main);
    SHW_ADR("Function", Function);
    SHW_ADR("cptr", cptr);
    SHW_ADR("buffer1", buffer1);
    int i = 0;
    SHW_ADR("i", i);
    strcpy(buffer1, "示例：");
    write(1, buffer1, strlen(buffer1) + 1);
    for (; i < 1; ++i)
    {
        Function(cptr);
    }
    return 0;
}