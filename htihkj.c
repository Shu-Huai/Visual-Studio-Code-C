#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100
/*
【问题描述】输入任意一行字符串(设字符数不大于80)，提取该字符串中的数字字符并组成一个整数，输出该整数及其两倍的值。
要求在主函数中输入字符串，并输出复制结果，在被调函数中完成提取该字符串中的数字字符并组成一个整数。
【输入形式】输入任意一行字符串。
【输出形式】提取该字符串中的数字字符并组成一个整数，输出该整数及其两倍的值。
【样例输入】（下划线部分为键盘输入，其余部分为程序输出）
Enter a string: ab34df6
【样例输出】
digit=346,692
*/
int number(char str[])
{
	int s = strlen(str);
	int i = 0, j = 0;
	int b[N];
	for (i = 0; i < s; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			b[j] = str[i] - 48;
			j++;
		}
	}
	int jisu = j;
	int sum = 0;
	for (j = 0; j < jisu; j++)
	{
		sum = sum + b[j] * pow(10, jisu - j - 1);
	}
	return sum;
}
int main()
{
	printf("Enter a string: ");
	char a[N];
	int i = 0;
	while (a[i - 1] != '\n')
	{
		a[i] = getchar();
		i++;
	}
	a[i] = '\0';
	int he = number(a);
	printf("digit=%d,%d", he, he * 2);
	return 0;
}