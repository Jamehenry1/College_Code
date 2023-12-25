#include "problem1.h"

int main(int argc, char **argv)
{

	if(argc != 2)
	{
		return 1;
	}

	FILE *fp = fopen(argv[1],"a+");

	if(fp == NULL)
	{
		return 1;
	}

	Creature c = { 0 };
	Creature *holder;

	char buffer[MAXSTRING];
	char *temp;
	int namelen = 0;
	int typelen = 0;
	int numCreatures = 0;

	int choice = 0;

	while(choice != 4)
	{

		printf("    Creature DB\n");
		printf("----------------------\n");
		printf("1. Add Creature\n2. View Creatures\n3. Sort Creatures\n4. Exit");
		scanf("%d",&choice);

		switch(choice)
		{

			case 1:
				
				break;
			case 2:
				

				while(1)
				{	
					fgets(buffer,MAXSTRING,fp);
					remove_newline(buffer);
					temp = strtok(buffer,",");

					if(feof(fp))
					{
						break;
					}

					namelen = strlen(temp);
					c->name = malloc(namelen * sizeof(char));
					strcpy(c->name,temp);

					printf("%s\n",c->name);

					temp = strtok(NULL,",");
					c->hp = atoi(temp);

					printf("%d\n", c->hp);

					temp = strtok(NULL,",");
					c->ac = atoi(temp);

					printf("%d\n", c->ac);

					temp = strtok(NULL,",");
					c->speed = atoi(temp);

					printf("%d\n", c->speed);

					temp = strtok(NULL,",");
					typelen = strlen(temp);
					c->name = malloc(typelen * sizeof(char));
					strcpy(c->name,temp);

					printf("%s\n",c->type);

					holder = realloc(holder, (numCreatures +1 ) * sizeof(c));

					holder[numCreatures] = *c;
					numCreatures++;

					//c = realloc(c,(numCreatures + 1) * sizeof(Creature));

					for(int i = 0; i < numCreatures - 1; i++)
					{
						//printf("%s\n", c-name);
					}
				}

				break;
			case 3:
				break;
			case 4:
				break;

			default:
				break;

		}
	}


	return 0;
}

void remove_newline(char *str) 
{
    int l = strlen(str);
    if (str[l - 1] == '\n') {
        str[l - 1] = 0;
    }
}

void fileRead(FILE *fp,Creature *c,Creature *holder)
{
	char buffer[MAXSTRING];
	char *temp;
	int namelen = 0;
	int typelen = 0;
	int numCreatures = 0;

	while(1)
	{	

	

		fgets(buffer,MAXSTRING,fp);
		remove_newline(buffer);
		temp = strtok(buffer,",");

		if(feof(fp))
		{
			break;
		}

		namelen = strlen(temp);
		c->name = malloc(namelen * sizeof(char));
		strcpy(c->name,temp);

		printf("%s\n",c->name);

		temp = strtok(NULL,",");
		c->hp = atoi(temp);

		printf("%d\n", c->hp);

		temp = strtok(NULL,",");
		c->ac = atoi(temp);

		printf("%d\n", c->ac);

		temp = strtok(NULL,",");
		c->speed = atoi(temp);

		printf("%d\n", c->speed);

		temp = strtok(NULL,",");
		typelen = strlen(temp);
		c->name = malloc(typelen * sizeof(char));
		strcpy(c->name,temp);

		printf("%s\n",c->type);

		//holder = realloc(holder, (numCreatures +1 ) * sizeof(c));

	


		



	}	

}