#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int kill(pid_t pid, int sig);
long DoEighteen()
{
    printf("进程：%d的18号信号的处理程序。\n", getpid());
    sleep(1);
    return 0;
}
int main()
{
    pid_t ID = fork();
    if (ID)
    {
        int result = kill(ID, 18);
        printf("父进程：%d向子进程：%d发送了18号信号，返回了：%d。\n", getpid(), ID, result);
        wait(0);
        printf("父进程：%d退出。\n", getpid());
        exit(0);
    }
    else
    {
        printf("子进程：%d收到了消息。\n子进程：%d退出。\n", getpid(), getpid());
        signal(18, (__sighandler_t)DoEighteen());
        exit(0);
    }
    return 0;
}