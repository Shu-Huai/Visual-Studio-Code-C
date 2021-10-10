#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
int main()
{
    printf("进程ID为：%d，父进程ID为：%d。\n", getpid(), getppid());
    for (int i = 0; i < 3; i++)
    {
        if (!fork())
        {
            printf("这是第%d个子进程的输出，ID为：%d，父ID为：%d。\n", i + 1, getpid(), getppid());
            exit(0);
        }
        else
        {
            pid_t childID = wait(0);
            printf("%d：我的子进程%d已经结束。\n", getpid(), childID);
        }
    }
    return 0;
}