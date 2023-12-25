#include <stdio.h>
#include <stdlib.h>

int main(){

	// (a)
	int *oneInt = malloc(sizeof(int));

	*oneInt = 20;
	printf("%d\n", *oneInt);
	free(oneInt);

	// (b)
	int x_b = 200;
	//printf("Enter number of values (b): ");
	//scanf("%d",&x_b);

	int *arrInt = malloc(x_b * sizeof(int));

	for(int i = 0; i < x_b; i++){
		arrInt[i] = 0;
		printf("%d = %d\n", i, arrInt[i]);
	}
	free(arrInt);

	// (c)
	int x_c = 30;
	int y_c = 40;
	//printf("Enter number of values (x,y) (c): ");
	//scanf("%d%d",&x_c, &y_c);

	int **arr2dInt = calloc(x_c, sizeof(int));

	for(int i = 0; i < x_c; i++){

		arr2dInt[i] = malloc(y_c * sizeof(int)); // this is x

		for(int j = 0; j < y_c; j++){

			arr2dInt[i][j] = 0;	//
			printf("%3d ", arr2dInt[i][j]);
		}
		printf("\n");

	}
	free(arr2dInt);

	// (d) -- (x,y,z)

	int x_d = 40;
	int y_d = 40;
	int z = 20;

	//printf("Enter number of values (x,y,z) (d): ");
	//scanf("%d%d%d",&x_d, &y_d,&z);

	int ***arr3dInt = calloc(z, sizeof(int)); 

	for(int i = 0; i < z; i++){

		arr3dInt[i] = malloc(x_d * sizeof(int)); // putting x in z

		for (int j = 0; j < x_d; j++){

			arr3dInt[i][j] = malloc(y_d * sizeof(int)); // putting y in x

			for (int k = 0; k < y_d; k++){

				arr3dInt[i][j][k] = 0;
				printf("%d", arr3dInt[i][j][k]);
			}
			printf("\n");
		}
		printf("\n");
		printf("------------------------------------------------------\n");
	}
	free(arr3dInt);
	
	// (e)
	double *oneDoub = malloc(sizeof(double));

	*oneDoub = 3.14;
	printf("%.2f\n", *oneDoub);
	free(oneDoub);

	// (f)

	int x_f = 300;
	//printf("Enter number of values (f): ");
	//scanf("%d",&x_f);

	double *arrDoub = calloc(x_f, sizeof(double));

	for(int i = 0; i < x_f; i++){
		arrDoub[i] = 0;
		printf("%.2f", arrDoub[i]);
	}
	printf("\n");
	free(arrDoub);


	// (g)

	int x_g = 80;
	int y_g = 80;
	//printf("Enter number of values (x,y) (g): ");
	//scanf("%d%d",&x_g, &y_g);

	double **arr2dDoub = calloc(x_g, sizeof(double));

	for(int i = 0; i < x_g; i++){

		arr2dDoub[i] = malloc(y_g * sizeof(double)); // this is x

		for(int j = 0; j < y_g; j++){

			arr2dDoub[i][j] = 0;	//
			printf("%f ", arr2dDoub[i][j]);
		}
		printf("\n");

	}
	free(arr2dDoub);


	// (h)
	char *character = malloc(sizeof(char));

	*character = 0;
	printf("%c\n", *character);

	free(character);


	// (i)

	int x_i = 2048;
	//printf("Enter number of values (i): ");
	//scanf("%d",&x_i);

	char *word = malloc(x_i * sizeof(char));

	for(int i = 0; i < x_i; i++){
		word[i] = 0;
		printf("%c", word[i]);
	}
	free(word);

	

	// (j)

	int x_j = 1024;
	int y_j = 1024;

	//printf("Enter number of values (x,y) (j): ");
	//scanf("%d%d", &x_j, &y_j);
	

	printf("%d %d\n", x_j, y_j);

	char **arr2dChar = malloc(x_j * sizeof(char));

	for(int i = 0; i < x_j; i++){

		arr2dChar[i] = malloc(y_j * sizeof(char));
		for (int j = 0; j < y_j; j++){
			arr2dChar[i][j] = 0;
			printf("%c", arr2dChar[i][j]);
		}
		printf("\n");
	}
	free(arr2dChar);

	return 0;
}