#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){

	if(argc != 3){
		return 1;
	}

	int N = atoi(argv[1]);
	int M = atoi(argv[2]);
	
	double *arr = malloc(sizeof(double) * N * M);

	for(int i = 0; i < N; i++){
		for (int j = 0; j < M; j++)
		{
			arr[i * M + j] = i * M + j;
			printf("%.2f ",arr[i * M + j]);
		}
	}

	free(arr);

	return 0;
}