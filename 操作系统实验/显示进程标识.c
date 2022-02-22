#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
begin:
    printf("进程标识：%d，组进程标识：%d，用户标识：%d。\n", getpid(), getgid(), getuid());
    sleep(5);
    system("ls /home/lvzhi");
    printf("是否退出？（Y/N）：");
    char input = 0;
    scanf("%c", &input);
    if (input == 'Y' || input == 'y')
    {
        return 0;
    }
    else
    {
        goto begin;
    }
    return 0;
}