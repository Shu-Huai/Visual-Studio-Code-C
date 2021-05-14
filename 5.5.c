#include <stdio.h>
#include <math.h>
int main()
{
	printf("Enter a string: ");
	char input[10];
	int number[10];
	int i = 0;
	while (i != -1)
	{
		input[i] = getchar();
		if (input[i] == '\n')
		{
			break;
		}
		if (input[i] >= '0' && input[i] <= '9')
		{
			number[i] = input[i] - 48;
		}
		else if (input[i] >= 'A' && input[i] <= 'F')
		{
			number[i] = input[i] - 55;
		}
		i++;
	}
	int result = 0;
	int length = i;
	for (i = length - 1; i >= 0; i--)
	{
		result += number[i] * pow(16, length - 1 - i);
	}
	printf("%d\n", result);
	return 0;
}