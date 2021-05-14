#include <stdio.h>
int main()
{
	printf("Enter 10 integers: ");
	int input[10] = {0};
	int i = 0;
	for (i = 0; i < 10; i++)
	{
		scanf("%d", &input[i]);
	}
	int x = 0;
	printf("Enter x: ");
	scanf("%d", &x);
	for (i = 0; i < x; i++)
	{
		int temp = input[0];
		int j = 0;
		for (j = 0; j < 9; j++)
		{
			input[j] = input[j + 1];
		}
		input[9] = temp;
	}
	for (i = 0; i < 10; i++)
	{
		printf("%d ", input[i]);
	}
	printf("\n");
	return 0;
}