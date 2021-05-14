#include <stdio.h>
int main()
{
	printf("Enter a string: ");
	char input[80];
	int i = 0;
	int count = 0;
	while (i != -1)
	{
		input[i] = getchar();
		if (input[i] == '\n')
		{
			break;
		}
		if (input[i] >= 'a' && input[i] <= 'z')
		{
			input[i] -= 32;
			count++;
		}
		i++;
	}
	int length = i;
	if (count == 0)
	{
		printf("no lowercase\n");
	}
	else
	{
		for (i = 0; i < length; i++)
		{
			putchar(input[i]);
		}
		printf("\n");
	}
	return 0;
}