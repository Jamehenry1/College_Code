#include <stdio.h>

int main()
{

	int num;
	int time = 0;

	printf("Enter an integer: ");
	scanf("%d",&num);

	for(int i = 1; (i < num)&&(time < 3); i++)
	{
		if(num % i == 0)
		{
			int x = num/i;
			printf("%5d\n",x);
			time++;

		}
		else if((i == (num-1))&&(num % i != 0)&&(time == 1))
		{
			printf("%5d is prime!\n",num);

		}

	}
		

	return 0;
	
}