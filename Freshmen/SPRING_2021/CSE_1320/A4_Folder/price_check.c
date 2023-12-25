#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 128



typedef struct 
{
	int id;
	char *name;
	float prices;
	int quantity;
}Items;

void parse(char *temp, Items *holder,float ourMaxPrice);

int main(int argc, char **argv)
{
	if(argc != 3)
	{
		return 1;
	}

	Items *holder;
	char *input_fname = argv[1];
	float input_price = atof(argv[2]);
	FILE *input_fp = NULL;
	char temp[MAXSIZE];

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
		fgets(temp, MAXSIZE, input_fp);
		//puts it into the struct and checks conditions for printing
		parse(temp, holder, input_price);


		//printf("Test2: %d, %s, %f, %d\n",holder->id,holder->name,holder->prices,holder->quantity );
	
	}

	printf("%f\n", input_price);

	fclose(input_fp);
	return 0;
}

void parse(char *temp, Items *holder,float ourMaxPrice)
{
	
	holder->id = atoi(strtok(temp, ","));
	holder->name = strtok(NULL, ",");
	holder->prices = atof(strtok(NULL, ","));
	holder->quantity = atoi(strtok(NULL, ","));

	if((ourMaxPrice >= holder->prices)&&(holder->quantity != 0))
	{
		printf("%s\n", holder->name);
	}

	//printf("Test: %d, %s, %f, %d\n",holder->id,holder->name,holder->prices,holder->quantity );
}