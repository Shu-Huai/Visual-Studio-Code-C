#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
int main()
{
    pid_t newPid = fork();
    if (newPid)
    {
        printf("在父进程中的输出。\n");
        newPid = wait(NULL);
        printf("ID为：%d的子进程已经结束。\n", newPid);
    }
    else
    {
        printf("这是子进程的输出。\n");
        exit(0);
    }
    return 0;
}