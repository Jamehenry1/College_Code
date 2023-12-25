#include <stdio.h>

#define size 225

void int_to_b3(short num, char arr[]);

int main()
{
	short num = 0;
	char arr[size];

	printf("Enter a number:\n");
	scanf("%hd", &num);

	int_to_b3(num,arr);

	return 0;
}

void int_to_b3(short num, char arr[])
{
	int remainder = 0;
	int decimal = num;
	int time = 0;
	int time2 = 0;
	char holdA[size];
	char temp[size];

	while (num != 0)
	{
		remainder = num%3;
		num = num/3;

		if(remainder == 0)
			holdA[time] = '0';
		else if(remainder == 1)
			holdA[time] = '1';
		else if(remainder == 2)
			holdA[time] = '2';
		else if(remainder == 3)
			holdA[time] = '3';
		time++;

	}
	for(int i = time-1; i >= 0; i--)
	{
		//printf("%c", holdA[i]);
		arr[time2] = holdA[i];
		time2++;
	}
	printf("%d decimal = %s base 3\n", decimal,arr);
}