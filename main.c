#include <stdio.h>
#include <stdlib.h>
#define N 100
#include <math.h>
/*
¡¾ÑùÀýÊäÈë1¡¿
12 693

¡¾ÑùÀýÊä³ö1¡¿
12*693=21*396
*/
int chai(int x, int a[])
{
	int i = 0;
	int temp = x;
	while (temp != 0)
	{
		a[i] = temp % 10;
		temp = temp / 10;
		i++;
	}
	int sum = 0;
	int temp2 = i;
	while (i != 0)
	{
		sum = sum + a[temp2 - i] * pow(10, i - 1);
		i--;
	}
	x = sum;
	return x;
}
int main()
{
	int x, y;
	int a[N], b[N];
	scanf("%d%d", &x, &y);
	printf("%d*%d", x, y);
	int sum1 = x * y;
	x = chai(x, a);
	y = chai(y, b);
	int sum2 = x * y;
	if (sum1 == sum2)
		printf("=%d*%d", x, y);
	else
		printf("!=%d*%d", x, y);
	return 0;
}