/*
Name: Nghia Lam 
ID: 1001699317 
1)gcc lab2.c 
2)./a.out < "name of file" or ./a.out 
3)user input if used ./a.out
*/

#include <stdio.h>
#include <stdlib.h>


int compare(const void *a, const void *b)
{
	int* arr1 = *(int**)a;
	int* arr2 = *(int**)b;
	//printf("break");
	//printf("Compare %d  <=> %d\n", arr1[3], arr2[3]);

	if(arr1[3] > arr2[3])
	{
		return 1;
	}
	else if(arr1[3] < arr2[3])
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

void arrHolder(int **washDry2D, int arrSize)
{
	int i = 0;
	for(i = 0; i < arrSize; i++) 
	{
		printf("\n%d\n",i);
		printf("\nEnter value (wash) (dry): ");
		scanf("%d %d", &washDry2D[i][1], &washDry2D[i][2]);
		//scanf("%d",&washDry2D[i][1]);
		//scanf("%d",&washDry2D[i][2]);

		//printf("%d:%d", washDry2D[i][1], washDry2D[i][2]);
		
		washDry2D[i][0] = i;

		if(washDry2D[i][1] < washDry2D[i][2])
		{
			washDry2D[i][3] = washDry2D[i][1];
		}
		else
		{
			washDry2D[i][3] = washDry2D[i][2];
		}
		
	}

}

int main()
{
	int arrSize = 0;
	printf("Enter number of arrays: ");
	scanf("%d",&arrSize);
 
	int **washDry2D = (int**)malloc(sizeof(int) * (arrSize+4));
	int johnSonArr[arrSize][3];
	
	int i = 0;

	for(i=0; i<arrSize; i++)
	{
    	washDry2D[i] = (int*)malloc(4*sizeof(int));
  	}

	arrHolder(washDry2D, arrSize);
	qsort(washDry2D, arrSize, sizeof(int*), compare);

	int indexA = 0;
	int indexB = arrSize-1;

	for(i = 0; i < arrSize; i++)
	{

		if(washDry2D[i][3] == washDry2D[i][1])
		{
			//move by A
			//printf("checkA: %d = %d\n",washDry2D[i][3], washDry2D[i][1]);
			johnSonArr[indexA][0] = washDry2D[i][0];
			johnSonArr[indexA][1] = washDry2D[i][1];
			johnSonArr[indexA][2] = washDry2D[i][2];
			//printf("%d %d %d \n",johnSonArr[indexA][0],johnSonArr[indexA][1],johnSonArr[indexA][2]);
			indexA++;
		}
		else
		{
			//move by B
			//printf("checkB : %d = %d\n",washDry2D[i][3], washDry2D[i][2]);
			johnSonArr[indexB][0] = washDry2D[i][0];
			johnSonArr[indexB][1] = washDry2D[i][1];
			johnSonArr[indexB][2] = washDry2D[i][2];
			//printf("%d %d %d \n",johnSonArr[indexB][0],johnSonArr[indexB][1],johnSonArr[indexB][2]);
			indexB--;

		}

	}

	printf("\n");
	int dryS = johnSonArr[0][1];
	int washS = 0;
	int next = 0;

	for(i = 0; i < arrSize; i++)
	{
		printf("%d %d %d %d %d\n",johnSonArr[i][0],johnSonArr[i][1],johnSonArr[i][2],washS,dryS);
		
		washS += johnSonArr[i][1];
		dryS += johnSonArr[i][2];


		next = i;
		
		if(dryS < ((washS+johnSonArr[++next][1])) && (i != (arrSize-1)))
		{
			printf("dryer gap from %d to %d\n", dryS,(washS+johnSonArr[next][1]));
			dryS = washS+johnSonArr[next][1];
			//printf("dryer gap from %d to %d\n", dryS,(washS+johnSonArr[next][1]));
		}
		
		if(i == (arrSize-1))
		{
			printf("makespan is: %d\n", dryS);
		}

	}

	for(i = 0; i < arrSize; i++)
	{
		free(washDry2D[i]);
	}

	free(washDry2D);

	return 0;

}
