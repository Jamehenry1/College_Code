#include <stdio.h>

int is_parallel(float arr1[], float arr2[]);

int main()
{
	float arr1[3];
	float arr2[3];

	printf("Enter values for ARRAY 1 [a] [b] [c] {ax + by = c}: ");
	scanf("%f%f%f", &arr1[0],&arr1[1],&arr1[2]);

	printf("Enter values for ARRAY 2 [a] [b] [c] {ax + by = c}: ");
	scanf("%f%f%f", &arr2[0],&arr2[1],&arr2[2]);

	int test = is_parallel(arr1,arr2);

	printf("{%d}\n",test);


	return 0;
}

int is_parallel(float arr1[], float arr2[])
{
	//calculate {ax + by = c} == {y = ax/b + c/b}
	//if arr1{a/b} = arr2{a/b} while the {c/b} of both arr1 and arr2 are different from each other

	float slope1 = arr1[0]/arr1[1];
	float slope2 = arr2[0]/arr2[1];

	float bValue1 = arr1[2]/arr1[1];
	float bValue2 = arr2[2]/arr2[1];

	if((slope1 == slope2)&&(bValue1 == bValue2))
	{
		//they are parallel and overlapping
		return 2;

	}
	else if(slope1 == slope2)
	{
		//they are parallel but not overlapping
		return 1;
	} 
	else
	{
		//not parallel
		return 0;
	}
}