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

	Creature c;
	Creature *creatureStorage = NULL;
	Creature addMonster;

	char name[MAXSTRING];
	char type[MAXSTRING];
	//int amountMonster = 0;

	int choice = 0;

	while(choice != 4)
	{

		char buffer[MAXSTRING];
		char *temp;
		int namelen = 0;
		int typelen = 0;
		int numCreatures = 0;
		int options = 0;

		fseek(fp,0,SEEK_SET);

		//reading the info hear-- could not get the values out of the read fuction so..... did it this way
		while(1)
		{	


			fgets(buffer,MAXSTRING,fp);

			//printf("%s\n", buffer);

			remove_newline(buffer);
			temp = strtok(buffer,",");

			//printf("---%s\n",buffer);

			
			//-------------------------------------------- Getting the monsters from file

			namelen = strlen(temp);
			c.name = malloc(namelen * sizeof(char));
			strcpy(c.name,temp);

			//printf("%s\n",c.name);

			temp = strtok(NULL,",");
			c.hp = atoi(temp);

			//printf("%d\n", c.hp);

			temp = strtok(NULL,",");
			c.ac = atoi(temp);

			//printf("%d\n", c.ac);

			temp = strtok(NULL,",");
			c.speed = atoi(temp);

			//printf("%d\n", c.speed);

			temp = strtok(NULL,",");
			typelen = strlen(temp);
			c.type = malloc(typelen * sizeof(char));
			strcpy(c.type,temp);



			//--------------------------------------------- Putting monsters in a struct array

			creatureStorage = realloc(creatureStorage,(numCreatures + 1) * sizeof(Creature));
			creatureStorage[numCreatures].name = c.name;
			creatureStorage[numCreatures].hp = c.hp;
			creatureStorage[numCreatures].ac = c.ac;
			creatureStorage[numCreatures].speed = c.speed;
			creatureStorage[numCreatures].type = c.type;

			numCreatures++;

			if(feof(fp))
			{
				break;
			}

		}	


		printf("\n    Creature DB\n");
		printf("----------------------\n");
		printf("1. Add Creature\n2. View Creatures\n3. Sort Creatures\n4. Exit\n");
		scanf("%d",&choice);
		getchar();

		switch(choice)
		{

			case 1:
				printf("Enter Name: ");
				fgets(name,MAXSTRING,stdin);
				remove_newline(name);
				addMonster.name = malloc(strlen(name) * sizeof(char));
				strcpy(addMonster.name,name);

				printf("Enter Type: ");
				fgets(type,MAXSTRING,stdin);
				remove_newline(type);
				addMonster.type = malloc(strlen(type) * sizeof(char));
				strcpy(addMonster.type,type);

				printf("Enter HP: ");
				scanf("%d",&addMonster.hp);

				printf("Enter AC: ");
				scanf("%d",&addMonster.ac);

				printf("Enter Speed: ");
				scanf("%d",&addMonster.speed);


				printf("%s,%d,%d,%d,%s\n",addMonster.name,addMonster.hp,addMonster.ac,addMonster.speed,addMonster.type);
				fprintf(fp, "\n%s,%d,%d,%d,%s",addMonster.name,addMonster.hp,addMonster.ac,addMonster.speed,addMonster.type);
				
				break;

			case 2:
				//fileRead(fp,c,creatureStorage);
				printStructArr(creatureStorage,numCreatures);
					
				break;

			case 3:
				printf("Select sort criteria (1. Name, 2. HP, 3. AC, 4. Speed, 5. Type)");
				scanf("%d", &options);

				if(options == 1)
					qsort(creatureStorage,numCreatures, sizeof(Creature),compareName);
				else if(options == 2)
					qsort(creatureStorage,numCreatures, sizeof(Creature),compareHP);
				else if(options == 3)
					qsort(creatureStorage,numCreatures, sizeof(Creature),compareAC);
				else if(options == 4)
					qsort(creatureStorage,numCreatures, sizeof(Creature),compareSpeed);
				else if(options == 5)
					qsort(creatureStorage,numCreatures, sizeof(Creature),compareType);
				else
					printf("NOT A VALID SORT OPTION");

				printStructArr(creatureStorage,numCreatures);
				break;

			case 4:
				return 1;
				break;

			default:
				printf("DID NOT TYPE IN A VAILD OPTION\n" );
				break;

		}

		creatureStorage = NULL;
	}

	//free(creatureStorage->name);
	free(addMonster.name);
	free(addMonster.type);
	free(creatureStorage);
	return 0;
}

void remove_newline(char *str) 
{
    int l = strlen(str);
    if (str[l - 1] == '\n') {
        str[l - 1] = 0;
    }
}

// it reads but could not get the struct array to transfer
void fileRead(FILE *fp,Creature c,Creature *creatureStorage)
{
	char buffer[MAXSTRING];
	char *temp;
	int namelen = 0;
	int typelen = 0;
	int numCreatures = 0;

	fseek(fp,0,SEEK_SET);

	while(1)
	{	


		fgets(buffer,MAXSTRING,fp);

		//printf("%s\n", buffer);

		remove_newline(buffer);
		temp = strtok(buffer,",");

		//printf("---%s\n",buffer);

		
		//-------------------------------------------- Getting the monsters from file

		namelen = strlen(temp);
		c.name = malloc(namelen * sizeof(char));
		strcpy(c.name,temp);

		//printf("%s\n",c.name);

		temp = strtok(NULL,",");
		c.hp = atoi(temp);

		//printf("%d\n", c.hp);

		temp = strtok(NULL,",");
		c.ac = atoi(temp);

		//printf("%d\n", c.ac);

		temp = strtok(NULL,",");
		c.speed = atoi(temp);

		//printf("%d\n", c.speed);

		temp = strtok(NULL,",");
		typelen = strlen(temp);
		c.type = malloc(typelen * sizeof(char));
		strcpy(c.type,temp);



		//--------------------------------------------- Putting monsters in a struct array

		creatureStorage = realloc(creatureStorage,(numCreatures + 1) * sizeof(Creature));
		creatureStorage[numCreatures].name = c.name;
		creatureStorage[numCreatures].hp = c.hp;
		creatureStorage[numCreatures].ac = c.ac;
		creatureStorage[numCreatures].speed = c.speed;
		creatureStorage[numCreatures].type = c.type;

		numCreatures++;

		if(feof(fp))
		{
			break;
		}

	}	

	for(int i = 0; i < numCreatures; i++)
	{
		printf("--------------------\n");
		printf("Name[%d]: %s\nHP: %d\nAC: %d\nSpeed: %d\nType: %s\n", i,
			creatureStorage[i].name,creatureStorage[i].hp,creatureStorage[i].ac,
			creatureStorage[i].speed,creatureStorage[i].type);
	}

	//return numCreatures;
}

int compareName(const void *elem1, const void *elem2)
{
	Creature *a = (Creature *)elem1;
	Creature *b = (Creature *)elem2;

	return strcmp(b->name,a->name);
}

int compareType(const void *elem1, const void *elem2)
{
	Creature *a = (Creature *)elem1;
	Creature *b = (Creature *)elem2;

	return strcmp(b->type,a->type);
}

int compareHP(const void *elem1, const void *elem2)
{
	Creature *a = (Creature *)elem1;
	Creature *b = (Creature *)elem2;

	return b->hp - a->hp;
}

int compareAC(const void *elem1, const void *elem2)
{
	Creature *a = (Creature *)elem1;
	Creature *b = (Creature *)elem2;

	return b->ac - a->ac;
}

int compareSpeed(const void *elem1, const void *elem2)
{
	Creature *a = (Creature *)elem1;
	Creature *b = (Creature *)elem2;

	return b->speed - a->speed;
}

void printStructArr(Creature *creatureStorage,int amountMonster)
{

	printf("\n\n%2s %-20s %4s %4s %6s %-15s\n","#","Name","HP","AC","SPEED","TYPE");
	for(int i = 0; i < amountMonster; i++)
	{
		printf("----------------------\n");
		printf("%2d %-20s %4d %4d %6d %-15s\n", i,
			creatureStorage[i].name,creatureStorage[i].hp,creatureStorage[i].ac,
			creatureStorage[i].speed,creatureStorage[i].type);


	}
}

void release_tree(Creature *root) 
{
    if (root != NULL) 
    {
        release_tree(root->left);
        release_tree(root->right);
        free(root);
    }
}