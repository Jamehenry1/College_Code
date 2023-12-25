#include <stdio.h>

int main()
{

	int a,b = 0;

	printf("\nEnter value of A: ");
	scanf("%d",&a);
	printf("\nEnter value of B: ");
	scanf("%d",&b);

	if((a == 1)&&(b == 1))
	{
		printf("\n (A&&B) = 1\n (A||B) = 1\n!(A||B) = 0\n");

	}
	else if((a == 1)||(b == 1))
	{
		printf("\n (A&&B) = 0\n (A||B) = 1\n!(A||B) = 0\n");

	}
	else
	{
		printf("\n (A&&B) = 0\n (A||B) = 0\n!(A||B) = 1\n");
	}


	return 0;
}