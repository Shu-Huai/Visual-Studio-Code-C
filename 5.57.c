#include <math.h>
#include <stdio.h>
int main()
{
	double input = 0;
	scanf("%lf", &input);
	int count = 1;
	double pie = 1;
	while (count)
	{
		double i = 0;
		double temp = 1;
		for (i = 1; i <= count; i++)
		{
			temp = temp * (2 * i) / (2 * i - 1) * (2 * i) / (2 * i + 1);
		}
		pie = temp * 2;
		double pieqian = temp / ((2 * i) / (2 * i - 1) * (2 * i) / (2 * i + 1)) * 2;
		double piehou = temp * ((2 * i) / (2 * i - 1) * (2 * i) / (2 * i + 1)) * 2;
		double chaqian = fabs(pieqian - input);
		double cha = fabs(pie - input);
		double chahou = fabs(piehou - input);
		if (chaqian >= cha && cha <= chahou)
		{
			break;
		}
		count++;
	}
	printf("%.9lf %d\n", pie, count);
	return 0;
}