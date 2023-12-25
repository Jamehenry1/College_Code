#include <stdio.h>
#include <float.h>

#define MAXVAL 8

float minCal(float arr[],int size);
float maxCal(float arr[],int size);
void sorting(float arr[],int size);
float medCal(float arr[]);
float meanCal(float arr[],int size);

int main()
{
	float numArr[MAXVAL];
	float sortNumArr[MAXVAL];

	float min = 0;
	float max = 0;
	float median = 0;
	float mean = 0;

	printf("Enter 8 values: ");
	scanf("%f %f %f %f %f %f %f %f",
		&numArr[0],&numArr[1],&numArr[2],&numArr[3],
		&numArr[4],&numArr[5],&numArr[6],&numArr[7]);

	for(int i = 0; i< 8; i++)
	{
		sortNumArr[i] = numArr[i];
		printf("%d = {%f}\n",i,sortNumArr[i]);

	}

	min = minCal(numArr,MAXVAL);
	printf("Min: {%3.2f}\n",min);

	max = maxCal(numArr,MAXVAL);
	printf("Max: {%3.2f}\n",max);

	sorting(sortNumArr,MAXVAL);

	median = medCal(sortNumArr);
	printf("Median: {%3.2f}\n",median);

	mean = meanCal(sortNumArr, MAXVAL);
	printf("Mean: {%3.2f}\n",mean);
	
	printf("Unsorted Array: ");
	for(int i = 0; i< MAXVAL; i++)
	{
		printf("{%4.2f} ",numArr[i]);

	}
	printf("\n");


	printf("Sorted Array: ");
	for(int i = 0; i< MAXVAL; i++)
	{
		printf("{%4.2f} ",sortNumArr[i]);

	}
	printf("\n");

	return 0;
}

void sorting(float arr[], int size)
{
	for(int i = 0; i < size; i++)
	{
		int min_j = i;

		for(int j = i+1; j < size; j++)
		{
			if(arr[min_j] < arr[j])
			{
				min_j = j;
			}
		}

		if(min_j != i)
		{
			int temp = arr[i];
			arr[i] = arr[min_j];
			arr[min_j] = temp;

		}

	}
}

float minCal(float arr[], int size)
{
	float lowest = 1000000;
	for(int i = 0; i < size; i++)
	{
		if(arr[i]<lowest)
		{
			lowest = arr[i];

		}
	}
	return lowest;
}

float maxCal(float arr[], int size)
{
	float highest = 0;
	float lowest = 1000000;
	for(int i = 0; i < size; i++)
	{
		if(arr[i]>highest)
		{
			highest = arr[i];

		}
	}
	return highest;
}

float medCal(float arr[])
{
	float medVal = 0;

	medVal = (arr[3] + arr[4])/2;
	return medVal;
}

float meanCal(float arr[], int size)
{
	float sum;
	for(int i = 0; i < size; i++)
	{
		sum += arr[i];

	}

	return sum/size;

}

