#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
int global = 100;
int main()
{
    int local = 100;
    printf("before fork.\n");
    printf("程序开始时，全局变量为：%d，局部变量为：%d。\n", global, local);
    if (!fork())
    {
        global++;
        local--;
        printf("子进程修改了全局变量和局部变量的值，此时全局变量为：%d，局部变量为：%d。\n", global, local);
        exit(0);
    }
    else
    {
        wait(NULL);
        printf("父进程中，此时全局变量为：%d，局部变量为：%d。\n", global, local);
    }
    return 0;
}