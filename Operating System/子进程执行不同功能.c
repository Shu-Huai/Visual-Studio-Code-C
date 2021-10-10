#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
int main()
{
    pid_t childID[3] = {0};
    for (int i = 0; i < 3; i++)
    {
        childID[i] = fork();
        if (!childID[i])
        {
            switch (i)
            {
            case 0:
                execlp("pwd", "pwd", (char *)0);
                exit(0);
                break;
            case 1:
                execlp("date", "date", (char *)0);
                exit(0);
                break;
            case 2:
                execlp("ls", "ls", "/home/lvzhi", (char *)0);
                exit(0);
                break;
            default:
                break;
            }
        }
    }
    pid_t pid = 0;
    int status = 0;
    while ((pid = wait(&status)) != -1)
    {
        if (childID[0] == pid)
        {
            printf("子进程1：%d结束，返回值为：%d。\n", pid, status);
        }
        else if (childID[1] == pid)
        {
            printf("子进程2：%d结束，返回值为：%d。\n", pid, status);
        }
        else if (childID[2] == pid)
        {
            printf("子进程3：%d结束，返回值为：%d。\n", pid, status);
        }
    }
    printf("父进程退出。\n");
    return 0;
}