#include <stdio.h>
int main()
{
    int geshu = 0;
    scanf("%d", &geshu);
    int i = 0;
    int input[21] = {0};
    for (i = 0; i < geshu; i++)
    {
        scanf("%d", &input[i]);
    }
    int cunchu[21] = {0};
    for (i = 0; i < geshu; i++)
    {
        cunchu[i] = input[i];
    }
    for (i = 0; i < geshu; i++)
    {
        int j = 0;
        for (j = 0; j < geshu; j++)
        {
            if (input[j] < input[i])
            {
                int temp = input[j];
                input[j] = input[i];
                input[i] = temp;
            }
        }
    }
    for (i = 1; i < geshu; i++)
    {
        if (input[i] == input[i + 1])
        {
            int j = 0;
            for (j = i; j < geshu; j++)
            {
                input[j] = input[j + 1];
            }
        }
    }
    for (i = 0; i < geshu; i++)
    {
        int j = 0;
        for (j = 0; j < geshu; j++)
        {
            if (cunchu[i] == input[j])
            {
                cunchu[i] = j + 1;
            }
        }
    }
    return 0;
}