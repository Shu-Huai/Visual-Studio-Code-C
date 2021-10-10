#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <unistd.h>
#define MSGKEY 75
struct MessageForm
{
    long m_type;
    char m_text[256];
} message;
int main()
{
    struct MessageForm message;
    int messageID = msgget(MSGKEY, 0777);
    pid_t pid = getpid();
    int *pint;
    pint = (int *)message.m_text;
    *pint = pid;
    message.m_type = 1;
    msgsnd(messageID, &message, sizeof(int), 0);
    msgrcv(messageID, &message, 256, pid, 0);
    printf("服务端的ID为：%d\n", *pint);
    return 0;
}