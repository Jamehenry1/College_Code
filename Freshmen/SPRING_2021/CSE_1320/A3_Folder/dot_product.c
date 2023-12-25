#include <stdio.h>
#define MAXNUM 8

double dot_product(double *arr1, double *arr2, int max);

int main()
{
	double arr1[8];
	double arr2[8];
	double total = 0;

	printf("Enter 8 numbers Array 1: ");
	scanf("%lf %lf %lf %lf %lf %lf %lf %lf"
		,&arr1[0],&arr1[1],&arr1[2],&arr1[3],&arr1[4],&arr1[5],&arr1[6],&arr1[7]);

	printf("Enter 8 numbers Array 2: ");
	scanf("%lf %lf %lf %lf %lf %lf %lf %lf"
		,&arr2[0],&arr2[1],&arr2[2],&arr2[3],&arr2[4],&arr2[5],&arr2[6],&arr2[7]);

	for(int i = 0; i < MAXNUM; i++)
	{
		printf("%lf\n", arr1[i]);
	}

	total = dot_product(arr1,arr2,MAXNUM);

	printf("Total: %lf\n", total);

	return 0;
}

double dot_product(double *arr1, double *arr2, int max)
{
	double sum = 0;
	for(int i = 0; i < max; i++)
	{
		sum = (arr1[i] * arr2[i]) + sum;
		printf("{i}: %lf\n",sum);
	}

	return sum;

}