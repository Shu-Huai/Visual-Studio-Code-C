#include <stdio.h>
long double GetFactorialByLoop(int number)
{
    if (number < 0)
    {
        return 0;
    }
    if (!number)
    {
        return 1;
    }
    int i = 0;
    long double result = 1;
    for (i = 0; i < number; i++)
    {
        result *= (i + 1);
    }
    return result;
}
long double GetFactorialByRecursion(long double number)
{
    if (number < 0)
    {
        return 0;
    }
    if (!number)
    {
        return 1;
    }
    return number * GetFactorialByRecursion(number - 1);
}
int main()
{
    int number = 0;
    printf("Please input a number: ");
    scanf("%d", &number);
    printf("The result of %d! by loop is: %.Lf.\n", number, GetFactorialByLoop(number));
    printf("The result of %d! by recursion is: %.Lf.\n", number, GetFactorialByRecursion(number));
    return 0;
}