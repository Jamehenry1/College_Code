#include <stdio.h>


void calculate(float arr[][2], float sumArr[], int count);
void min(float arr[][2], float min[], int place, int count);
void max(float arr[][2], float max[], int place, int count);

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		return 1;
	}

	char *input_fname = argv[1];
	FILE *input_fp = NULL;

	input_fp = fopen(input_fname,"r");

	if(input_fp == NULL)
	{
		printf("CANNOT OPEN FILE\n");
		return 1;
	}

	int x = 0;
	int y = 1;

	typedef float vector2f[2];
	vector2f dataArray[30];
	vector2f midPoint;
	vector2f minValue;
	vector2f maxValue;

	int i = 0;

	/*
	dataArray[0][1] = 8.4;
	dataArray[1][0] = 9.4;
	printf("%f\n", dataArray[0][1]);
	printf("%f\n", dataArray[1][0]);
	*/
	while(1)
	{
		fscanf(input_fp,"%f,%f", &dataArray[i][0], &dataArray[i][1]);

		if(feof(input_fp))
		{
			break;
		}

		printf("%f,%f\n", dataArray[i][0], dataArray[i][1]);
		i++;

	}

	calculate(dataArray,midPoint,i);
	min(dataArray,minValue,x,i);
	min(dataArray,minValue,y,i);

	max(dataArray,maxValue,x,i);
	max(dataArray,maxValue,y,i);

	printf("Min Values: %f,%f\n",minValue[0],minValue[1]);
	printf("Max Values: %f,%f\n",maxValue[0],maxValue[1]);

	printf("%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n", minValue[x],minValue[y],maxValue[x],maxValue[y],midPoint[x],midPoint[y]);

	fclose(input_fp);

	return 0;
}

void calculate(float arr[][2], float sumArr[], int count)
{
	float tempX = 0;
	float tempY = 0;

	for(int j = 0; j < count; j++)
	{
		tempX += arr[j][0];
		tempY += arr[j][1];
	}
	sumArr[0] = tempX/count;
	sumArr[1] = tempY/count;

	printf("Values: %f,%f\n",sumArr[0],sumArr[1]);
}

void min(float arr[][2], float min[], int place, int count)
{
	for(int i = 0; i < count; i++)
	{
		if(min[place] > arr[i][place])
		{
			min[place] = arr[i][place];
		}
	}
}

void max(float arr[][2], float max[], int place, int count)
{
	for(int i = 0; i < count; i++)
	{
		if(max[place] < arr[i][place])
		{
			max[place] = arr[i][place];
		}
	}
}

