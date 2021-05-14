#include <stdio.h>
int main()
{
    char input[1000] = {'0'};
    int i = 0;
    while (input[i - 1] != '\n')
    {
        scanf("%c", &input[i]);
        i++;
    }
    int length = i - 1;
    for (i = 0; i < length; i++)
    {
        int j = 0;
        for (j = i; j < length; j++)
        {
            if (input[i] > input[j])
            {
                int temp = input[j];
                input[j] = input[i];
                input[i] = temp;
            }
        }
    }
    int test = 1;
    for (i = 1; i < length; i++)
    {
        if (input[i] == input[i - test])
        {
            input[i] = '\0';
            test++;
        }
        else
        {
            test = 1;
        }
    }
    for (i = 0; i < length; i++)
    {
        if (input[i] != '\000')
        {
            printf("%c", input[i]);
        }
    }
    return 0;
}