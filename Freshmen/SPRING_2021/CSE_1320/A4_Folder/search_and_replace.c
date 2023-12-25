#include <stdio.h>


int main(int argc, char **argv)
{
	if(argc != 5)
	{
		return 1;
	}

	char *input_fname = argv[1];
	char *output_fname = argv[2];
	FILE *input_fp = NULL;
	FILE *output_fp = NULL;
	char temp = 0;
	char *search = argv[3];
	char *replace = argv[4];
	int counter = 0;

	input_fp = fopen(input_fname, "r");

	if(input_fp == NULL)
	{
		printf("WARING CANNOT FIND FILE\n");
		return 1;
	}

	output_fp = fopen(output_fname, "w");

	if(output_fp == NULL)
	{
		return 1; 
	}
	printf("DESTINATION FILE EXISTS\n");

	while((temp = getc(input_fp)) != EOF)
	{
		
		
		if(temp == *search)
		{
			temp = *replace;
			counter++;
		}
		
		putc(temp,output_fp);
	}
	printf("%d characters changed\n", counter);


	fclose(input_fp);
	fclose(output_fp);

	return 0;


}