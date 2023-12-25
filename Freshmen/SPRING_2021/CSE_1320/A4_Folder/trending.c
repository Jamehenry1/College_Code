#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNUM 120
#define MAXNUMCHAR 128

int trendcheck(char words[][MAXNUMCHAR],char trendword[]);

int main(int argc, char **argv)
{	
	if(argc != 3)
	{
		return 1;
	}

	char *input_fname = argv[1];
	char *trendword = argv[2];
	char temp[MAXNUMCHAR];
	FILE *input_fp = NULL;
	int trendCount = 0;
	int increment = 0;
	char words[MAXNUM][MAXNUMCHAR];

	input_fp = fopen(input_fname,"r");
	if(input_fp == NULL)
	{
		printf("CANNOT OPEN FILE\n");
		return 1;
	}

	while(1)
	{
		if(feof(input_fp))
		{
			break;
		}

		fscanf(input_fp,"%s", words[increment]);

		increment++;

	}

	int check = trendcheck(words,trendword);

	if(check == 1)
	{
		for(int i = 0; i < increment; i++)
		{
			if((strcmp(words[i],trendword)) == 0)
			{
				trendCount++;
			}

		}

		printf("\"%s\" is trending with %d\n",trendword, trendCount);
	}
	else
	{
		printf("\"%s\" is not trending\n", trendword);
	}
	
	fclose(input_fp);

	return 0;
}

int trendcheck(char words[][128],char trendword[])
{

	int count = 0;

	for(int i = 0; i < MAXNUM; i++)
	{
		if((strcmp(words[i],trendword)) == 0)
		{
			count++;
		}

		if(count > 3)
		{
			return 1;
		}
	}

	return 0;

}

