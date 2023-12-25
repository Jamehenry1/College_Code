/*
Name: Nghia Lam 
ID: 1001699317 
1)gcc lab1.c 
2)./a.out < "name of lab" or ./a.out 
3)user input if used ./a.out
*/
#include <stdio.h>
#include <stdlib.h>

void arrayHolder(int *arr, int size) // puts the values inside the arrays
{
	int i = 1;
	for(i = 1; i < size - 1; i++)
	{
		printf("Enter number: ");
		scanf("%d", &arr[i]);
		//printf("\nArray[%d]: %d\n", i, arr[i]);
	}
}

void printArray(int *arr, int size) // prints out values in each array
{
	int i = 1;
	for(i = 0; i < size; i++)
	{		
		printf("\nArray[%d]: %d\n", i, arr[i]);
	}
}

//prints output information
void printInfo(int low, int high, int i, int iAfter, int j, int jAfter, int a1 , int a2, int b1, int b2, int done)
{
	if(done != 1 && a2 <= b2)
	{
		printf("low %d high %d i %d j %d a[%d]=%d b[%d]=%d a[%d]=%d\n", low, high, i, j, i,a1,j,b1,iAfter,a2 );
	}
	else if(done != 1 && b2 < a2)
	{
		printf("low %d high %d i %d j %d b[%d]=%d a[%d]=%d b[%d]=%d\n", low, high, i, j, j,b1,i,a1,jAfter,b2 );
	}
}

void rankFinder(int *arrA, int *arrB, int rank, int sizeA, int sizeB)
{
	int done = 0;
	int high,low,mid = 0;

	
	if(rank <= (sizeA-2))
	{
		high = rank;
		low = 0;
		
	}
	else
	{
		high = (sizeA - 2);
		if((sizeB-2) < rank)
			low = rank - (sizeB - 2);
		else
			low = 0;
	}

	int a0,b0,a1,a2,b1,b2 = 0; //values of A and B arrays
	int bPoint = 0;



	while(done != 1)
	{
		mid = (high + low)/2;
		bPoint = rank - mid;
		
		int i = mid;
		int j = bPoint;

		int iAfter = i+1;
		int jAfter = j+1;
		int iBefore = i-1;
		int jBefore = j-1; 

		a1 = arrA[i];
		a2 = arrA[iAfter];
		a0 = arrA[iBefore];
		b1 = arrB[j];
		b2 = arrB[jAfter];
		b0 = arrB[jBefore];
		//printf("a2[%d]=%d b2[%d]=%d\n",iAfter,a2, jAfter,b2);
  		
		if( ((a2 < a1) || (a2 < b1)) ) // 
		{
			//Checking and printing for ABA
			//printf("low %d high %d i %d j %d a[%d]=%d b[%d]=%d a[%d]=%d\n", low, high, i, j, i,arrA[i],j,arrB[j],iAfter,arrA[iAfter] );
			printInfo(low, high, i, iAfter, j, jAfter, a1 , a2, b1, b2, done);

			low = mid + 1;
			
		}	//	    |     looking ABA      |      |      looking BAB     |  
		else if( (( (a2 >= a1) && (a2 >= b1)) && ((b2 >= b1) && (b2 >= a1) )) || (high == low) ) //if all values 
		{

			if(((i+j) == rank) && (a1 <= b1) && (b1 < a2))
			{
				//Checking and printing for ABA
				printf("low %d high %d i %d j %d a[%d]=%d b[%d]=%d a[%d]=%d\n", low, high, i, j, i,arrA[i],j,arrB[j],iAfter,arrA[iAfter] );
				printf("b[%d]=%d has rank %d\n\n",j,arrB[j],rank);
				done = 1;
			}
			else if(((i+j) == rank) && (b1 < a1) && (a1 <= b2))
			{
				//Checking and printing for BAB
				printf("low %d high %d i %d j %d b[%d]=%d a[%d]=%d b[%d]=%d\n", low, high, i, j, j,arrB[j],i,arrA[i],jAfter,arrB[jAfter] );
				printf("a[%d]=%d has rank %d\n\n",i,arrA[i],rank);
				done = 1;
			}
			else if( (b1 >= a2) ) //checks if arrB[j] is greater than arr[++i] if it is then low has to go up
			{			
				printInfo(low, high, i, iAfter, j, jAfter, a1 , a2, b1, b2, done);
				low = mid + 1;
			}
			else if( ((b0 < b1) && (b0 >= a1)) && ((low + high) <= rank) && (rank != 1)) //Check if values of arrB[--j] 
			{
				//Printed BAB because there was a value of b0 that could exsist inbetween a1 and b1
				//printf("-low %d high %d i %d j %d b[%d]=%d a[%d]=%d b[%d]=%d\n", low, high, i, j, j,arrB[j],i,arrA[i],jAfter,arrB[jAfter] );
				
				printInfo(low, high, i, iAfter, j, jAfter, a1 , a2, b1, b2, done);
				low = mid + 1;
			}
		
		}
		else if( ((b2 < a1) || (b2 < b1)) ) //If arr[j++] works for both conditions, if it does no work then high has to go down
		{
			printInfo(low, high, i, iAfter, j, jAfter, a1 , a2, b1, b2, done);
			high = mid-1;
		}
		else
		{
			printf("error?");
			done = 1;
		}


	}

}


int main()
{
	int *arrA;
	int *arrB;
	int *ranksArr;

	int aSize,bSize,numRanks;

	printf("Enter your values: ");
	scanf("%d %d %d",&aSize,&bSize,&numRanks);

	aSize = aSize + 2;
	bSize = bSize + 2;
	numRanks = numRanks + 2;

	arrA = malloc(sizeof(int) * aSize);
	arrB = malloc(sizeof(int) * bSize);
	ranksArr = malloc(sizeof(int) * numRanks);



	arrA[0] = -999999;
	arrB[0] = -999999;
	ranksArr[0] = -999999;

	arrA[aSize - 1] = 999999;
	arrB[bSize - 1] = 999999;
	ranksArr[numRanks - 1] = 999999;

	arrayHolder(arrA, aSize);
	arrayHolder(arrB, bSize);
	arrayHolder(ranksArr, numRanks);

	printArray(arrA, aSize);
	printArray(arrB, bSize);
	printArray(ranksArr, numRanks);
	//int position = 0;

	//the for loop for the ranking inputs to the fuction
	int i = 1;
	for(i = 1; i < (numRanks - 1); i++)
	{
		rankFinder(arrA,arrB,ranksArr[i],aSize,bSize);
	}
	free(arrA);
	free(arrB);
	free(ranksArr);

	return 0;

	

}
