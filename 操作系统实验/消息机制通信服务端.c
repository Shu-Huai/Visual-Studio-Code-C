#include <signal.h>
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
    extern void CleanUp();
    for (int i = 0; i < 20; i++)
    {
        signal(i, CleanUp);
    }
    int messageID = msgget(MSGKEY, 0777 | IPC_CREAT);
    while (msgrcv(messageID, &message, 256, 1, 0))
    {
        int *pint;
        pint = (int *)message.m_text;
        int pid = *pint;
        printf("服务端收到客户端ID为：%d的消息。\n", pid);
        message.m_type = pid;
        *pint = getpid();
        msgsnd(messageID, &message, sizeof(int), 0);
    }
    return 0;
}
void CleanUp(int messageID)
{
    msgctl(messageID, IPC_RMID, 0);
    exit(0);
}