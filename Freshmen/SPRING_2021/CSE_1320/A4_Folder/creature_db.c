#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXSTRLEN 128

typedef struct
{
	char name[MAXSTRLEN];
	int cr;
	int ac;
	int hp;

}Creature;

void remove_newline(char *str);

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		return 1;

	}

	Creature creature = { 0 };

	char *fileName = argv[1];
	FILE *file_pf = NULL;
	int count = 0;

	file_pf = fopen(fileName,"r+");

	if(file_pf == NULL)
	{
		printf("--WARNING CANNOT READ, INVALID FILE INPUT\n--Created \"%s\" as the a the new file\n", fileName);
		file_pf = fopen(fileName,"w+");
	}

	if(file_pf == NULL)
	{
		printf("WARING 2 STILL CANNOT READ FILE\n");
		return 1;
	}


	int choice;

	while(choice != 3)
	{

		printf("\n1. List Creatures\n2. Add Creatures\n3. Exit\nEnter your choice: ");
		scanf("%d",&choice);
		getchar();

		switch(choice)
		{
			
			case (1): 
			{	

				Creature cRead;
				fseek(file_pf, 0,SEEK_SET);
				//fread(&cRead, sizeof(Creature), 1, file_pf);
		
				while(fread(&cRead, sizeof(Creature), 1, file_pf))
				{
					printf("\n%s\n", cRead.name);

					for(int i = 0; i< strlen(cRead.name); i++)
					{
						printf("-");	
					}

					printf("\nCR: %d\n", cRead.cr);
					printf("AC: %d\n", cRead.ac);
					printf("HP: %d\n", cRead.hp);
				}

				break;
			}

			case (2):
			{
				fseek(file_pf, 0, SEEK_END);
				
				printf("Enter name: ");
				fgets(creature.name, MAXSTRLEN, stdin);
				remove_newline(creature.name);

				printf("Enter Challenge Rating: ");
				scanf("%d", &creature.cr);

				printf("Enter Armor Class: ");
				scanf("%d", &creature.ac);

				printf("Enter Hit Points: ");
				scanf("%d", &creature.hp);	

				printf("\nCreature added!\n");

				fwrite(&creature, sizeof(Creature), 1, file_pf);
				count++;
				break;
			}

			case (3):
			{
				break;
			}

			default:
			{
				printf("INVALID CHOICE\n");
			}

		}
		//return 0;
	}
	


	//switch 
	fclose(file_pf);
	return 0;
}

void remove_newline(char *str)
{
	int length = strlen(str);

	if(str[length - 1] == '\n')
	{
		str[length - 1] = 0;
	}
}



