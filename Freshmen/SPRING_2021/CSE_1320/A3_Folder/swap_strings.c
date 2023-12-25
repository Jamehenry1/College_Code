#include <stdio.h>

void swap_strings(char *arr1[], char *arr2[],int index1,int index2);

int main()
{
	char *arr1[] = {"One","Two","Three","Four"};
	char *arr2[] = {"Five","Six","Seven","Eight"};
	int index1 = 0;
	int index2 = 0;

	printf("Arr1 \t%12s\n", "Arr2");
	for(int i = 0; i < 4; i++)
	{
		printf("{%d}: %-8s",i, arr1[i]);
		printf("\t{%d}: %-8s\n",i, arr2[i]);

	}
	printf("Enter 2 index values between 0 - 3: \n");
	scanf("%d %d",&index1,&index2);

	swap_strings(arr1,arr2,index1,index2);
	
	return 0;
}

void swap_strings(char *arr1[], char *arr2[],int index1,int index2)
{

	char *temp;
	//printf("Work\n");
	printf("\nArr1 \t%12s\n", "Arr2");
	//temp = arr1[index1];
	//printf("%s\n", temp);


	temp = arr1[index1];
	arr1[index1] = arr2[index2];
	arr2[index2] = temp;


	

	for(int j = 0; j < 4; j++)
	{
		printf("{%d}: %-8s",j, arr1[j]);
		printf("\t{%d}: %-8s\n",j, arr2[j]);
	
	}
}