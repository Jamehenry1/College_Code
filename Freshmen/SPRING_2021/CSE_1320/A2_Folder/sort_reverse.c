#include <stdio.h>

void sort_reverse(int arr[], int size);

int main()
{
	int numArr[8];
	scanf("%d %d %d %d %d %d %d %d",
	&numArr[0],&numArr[1],&numArr[2],&numArr[3],
	&numArr[4],&numArr[5],&numArr[6],&numArr[7]);

	for(int i = 0; i< 8; i++)
	{
		printf("{%4d} ",numArr[i]);

	}

	sort_reverse(numArr,8);

	for(int i = 0; i < 8; i++)
	{
		printf("%d\n",numArr[i]);
	}
	return 0;
}

void sort_reverse(int arr[], int size)
{   
	// sort array  
	int count = 0;

 	for (int i = size; i >= 0; i--) 
 	{        
 		int min_j = i;      
   		for (int j = i - 1; j >= 0; j--)
    	{           
    		if (arr[j] < arr[min_j]) 
    		{   
     			min_j = j; 
     			count++;      
        	}   

    	}     

        // Swap values     
        if (min_j != i) 
        { 
            int temp = arr[i]; 
            arr[i] = arr[min_j]; 
            arr[min_j] = temp;  
		}   
	}

	printf("Count: %d\n",count);

}
