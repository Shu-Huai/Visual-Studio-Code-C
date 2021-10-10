#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/wait.h>
#include <unistd.h>
int lockf(int __fd, int __cmd, off_t __len);
int main()
{
    int fd[2];
    char buffer[50];
    pipe(fd);
    pid_t p1 = fork();
    if (!p1)
    {
        lockf(fd[1], 1, 0);
        sprintf(buffer, "第一个子进程发送的消息。\n");
        printf("第一个子进程发送了消息：%s", buffer);
        write(fd[1], buffer, 50);
        lockf(fd[1], 0, 0);
        sleep(1);
        printf("子进程一：%d退出，父进程：%d。\n", getpid(), getppid());
        exit(0);
    }
    else
    {
        pid_t p2 = fork();
        if (!p2)
        {
            lockf(fd[1], 1, 0);
            sprintf(buffer, "第二个子进程发送的消息。\n");
            printf("第二个子进程发送了消息：%s", buffer);
            write(fd[1], buffer, 50);
            lockf(fd[1], 0, 0);
            sleep(1);
            printf("子进程二：%d退出，父进程：%d。\n", getpid(), getppid());
            exit(0);
        }
        else
        {
            char result[50] = {0};
            read(fd[0], result, 50);
            printf("父进程收到的消息：%s", result);
            read(fd[0], result, 50);
            printf("父进程收到的消息：%s", result);
            printf("父进程：%d退出\n。", getpid());
            exit(0);
        }
    }
    return 0;
}