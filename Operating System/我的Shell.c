#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define OUTRED 1
#define INRED 2
#define HAVEPIPE 3
void GetInput(char *buffer)
{
    int length = 0;
    int ch = getchar();
    while (length < 256 && ch != '\n')
    {
        buffer[length++] = ch;
        ch = getchar();
    }
    if (length == 258)
    {
        printf("命令过长。\n");
        exit(-1);
    }
    buffer[length] = '\n';
    buffer[length + 1] = '\0';
}
void Explain(char *buffer, int *argCount, char argList[100][256])
{
    char *p = buffer;
    char *q = buffer;
    int number = 0;
    while (p[0] != '\n')
    {
        if (p[0] == ' ')
        {
            p++;
        }
        else
        {
            q = p;
            number = 0;
            while (q[0] != ' ' && q[0] != '\n')
            {
                number++;
                q++;
            }
            strncpy(argList[*argCount], p, number + 1);
            argList[*argCount][number] = '\0';
            *argCount += 1;
            p = q;
        }
    }
}
int FindCommand(char *command)
{
    DIR *dp;
    struct dirent *drip;
    char *path[] = {"./", "/bin", "/usr/bin", "/usr/local/bin", "/usr/local/sbin", "/usr/sbin", "/sbin", NULL};
    if (strncmp(command, "/", 2) == 0)
    {
        command = command + 2;
    }
    int i = 0;
    while (path[i])
    {
        if (!(dp = opendir(path[i])))
        {
            printf("路径错误。\n");
        }
        while (drip = readdir(dp))
        {
            if (!strcmp(drip->d_name, command))
            {
                closedir(dp);
                return 1;
            }
        }
        closedir(dp);
        i++;
    }
    return 0;
}
void Execute(int argCount, char argList[100][256])
{
    int flag = 0;
    int how = 0;
    int background = 0;
    int status = 0;
    int i;
    int fd;
    char *arg[argCount + 1];
    char *argNext[argCount + 1];
    char *file;
    pid_t pid;
    for (i = 0; i < argCount; i++)
    {
        arg[i] = (char *)argList[i];
    }
    arg[argCount] = NULL;
    for (i = 0; i < argCount; i++)
    {
        if (strncmp(arg[i], "&", 1) == 0)
        {
            if (i == argCount - 1)
            {
                background = 1;
                arg[argCount - 1] = NULL;
                break;
            }
            else
            {
                printf("指令错误。\n");
                return;
            }
        }
    }
    for (i = 0; arg[i]; i++)
    {
        if (strcmp(arg[i], ">") == 0)
        {
            flag++;
            how = OUTRED;
            if (!arg[i + 1])
            {
                flag++;
            }
        }
        if (strcmp(arg[i], "<") == 0)
        {
            flag++;
            how = INRED;
            if (i == 0)
            {
                flag++;
            }
        }
        if (strcmp(arg[i], "|") == 0)
        {
            flag++;
            how = HAVEPIPE;
            if (!arg[i + 1])
            {
                flag++;
            }
            if (i = 0)
            {
                flag++;
            }
        }
    }
    if (flag > 1)
    {
        printf("指令错误。\n");
        return;
    }
    if (how == OUTRED)
    {
        for (i = 0; arg[i]; i++)
        {
            if (strcmp(arg[i], ">") == 0)
            {
                file = arg[i + 1];
                arg[i] = NULL;
            }
        }
    }
    if (how == INRED)
    {
        for (i = 0; arg[i]; i++)
        {
            if (strcmp(arg[i], "<") == 0)
            {
                file = arg[i + 1];
                arg[i] = NULL;
            }
        }
    }
    if (how == HAVEPIPE)
    {
        for (i = 0; arg[i]; i++)
        {
            if (strcmp(arg[i], "|") == 0)
            {
                arg[i] = NULL;
                int j = i + 1;
                for (j = i + 1; arg[j]; j++)
                {
                    argNext[j - i - 1] = arg[j];
                }
                argNext[j - i - 1] = arg[j];
                break;
            }
        }
    }
    if (pid = fork() < 0)
    {
        printf("创建子进程失败。\n");
        return;
    }
    switch (how)
    {
    case 0:
        if (pid == 0)
        {
            if (!FindCommand(arg[0]))
            {
                printf("没有这个命令。\n");
                exit(0);
            }
            execvp(arg[0], arg);
            exit(0);
        }
        break;
    case 1:
        if (pid == 0)
        {
            if (!FindCommand(arg[0]))
            {
                printf("没有这个命令。\n");
                exit(0);
            }
            fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
            dup2(fd, 1);
            close(fd);
            execvp(arg[0], arg);
            exit(0);
        }
        break;
    case 2:
        if (pid == 0)
        {
            if (!FindCommand(arg[0]))
            {
                printf("没有这个命令。\n");
                exit(0);
            }
            fd = open(file, O_RDONLY);
            dup2(fd, 0);
            execvp(arg[0], arg);
            exit(0);
        }
        break;
    case 3:
        if (pid == 0)
        {
            int pid2;
            int status2;
            int fd2;
            if (pid2 = fork() < 0)
            {
                printf("创建子进程失败。\n");
                return;
            }
            else if (pid2 == 0)
            {
                if (!FindCommand(arg[0]))
                {
                    printf("没有这个命令。\n");
                    exit(0);
                }
                fd2 = open("/tmp/youdonotknowfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
                dup2(fd2, 0);
                execvp(arg[0], arg);
                exit(0);
            }
            if (waitpid(pid2, &status2, 0) < 0)
            {
                printf("等待子进程失败。\n");
            }
            if (!FindCommand(argNext[0]))
            {
                printf("没有这个命令。\n");
                exit(0);
            }
            fd2 = open("/tmp/youdonotknowfile", O_RDONLY);
            dup2(fd2, 0);
            execvp(argNext[0], argNext);
            if (remove("/tmp/youdonotknowfile"))
            {
                printf("等待子进程失败。\n");
            }
            exit(0);
        }
        break;
    default:
        break;
    }
    if (background == 1)
    {
        printf("进程id：%d。\n", pid);
        return;
    }
    if (waitpid(pid, &status, 0) < 0)
    {
        printf("等待错误。\n");
    }
}
int main(int argc, char **argv)
{
    int argCount = 0;
    char argList[100][256];
    char **arg = NULL;
    char *buffer = NULL;
    buffer = (char *)malloc(256);
    if (!buffer)
    {
        perror("内存分配错误。");
        exit(-1);
    }
    while (1)
    {
        memset(buffer, 0, 256);
        printf("我的Shell：");
        GetInput(buffer);
        if (strcmp(buffer, "exit\n") == 0 || strcmp(buffer, "logout\n") == 0)
        {
            printf("再见。\n");
            break;
        }
        for (int i = 0; i < 100; i++)
        {
            argList[i][0] = '\0';
        }
        argCount = 0;
        Explain(buffer, &argCount, argList);
        Execute(argCount, argList);
    }
    if (buffer)
    {
        free(buffer);
        buffer = NULL;
    }
    exit(0);
}