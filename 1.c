#include <stdio.h>
int main()
{
    int jinjia = 0;
    int shoujia = 0;
    int jianshu = 1;
    double shouyi = 0;
    scanf("%d %d", &jinjia, &shoujia);
    double temp = 0;
    while (jianshu)
    {
        shouyi = shoujia * jianshu * (1 - 0.01 * jianshu) - jinjia * jianshu;
        if (shouyi < temp)
        {
            break;
        }
        temp = shouyi;
        jianshu++;
    }
    printf("%d:%.2lf\n", jianshu - 1, temp);
    return 0;
}