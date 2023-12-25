#include "problem3.h"

int main(int argc, char **argv)
{

	if(argc != 2)
	{
		return 1;
	}

	FILE *fp = fopen(argv[1],"r");

	if(fp == NULL)
	{
		return 1;
	}

	Creature c;
	

	int choice = 0;

	

	char buffer[MAXSTRING];
	char *temp;
	int namelen = 0;
	int typelen = 0;
	Node *head = NULL;
	char type[MAXSTRING];
	Node *TypeNode = NULL;


	//reading the info hear-- could not get the values out of the read fuction so..... did it this way
	while(1)
	{	
	
		fgets(buffer,MAXSTRING,fp);
		temp = strtok(buffer,",");


		
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

		head = insertNode(head,c);

		//--------------------------------------------- Putting monsters in a struct array
	
		if(feof(fp))
		{
			break;
		}

	}	

	printf("Enter the type you want to search\n");
	fgets(type,MAXSTRING,stdin);
	traverse(head,type,TypeNode);
		
	

	//free(creatureStorage->name);

	return 0;
}

Node *addNode(Creature data)
{
	Node *n = calloc(1,sizeof(Node));
	//printf("1:%s\n", data.name);
	n->data.name = malloc(strlen(data.name) + 1);
	printf("2:%s\n", n->data.name);
	strcpy(n->data.name,data.name);
	printf("2:%s\n", n->data.name);
	n->data.hp = data.hp;
	printf("2:%d\n", n->data.hp);
	n->data.ac = data.ac;
	printf("2:%d\n", n->data.ac);
	n->data.speed = data.speed;
	printf("2:%d\n", n->data.speed);

	n->data.type = malloc(strlen(data.type) + 1);
	strcpy(n->data.type,data.type);

	return n;

}

Node *insertNode(Node *head, Creature data)
{
	Node *newNode = addNode(data);

	newNode->next = head;

	return newNode;
}

void traverse(Node *n,char *type,Node *TypeNode) {

	Creature adding;
	strcat(n->data.type,"\n");

    while (n != NULL) {
    	//remove_newline(n->data.type);
    	//remove_newline(type);
    	//strcat(n->data.type,"\n");
        
       	//printf("%d\n",strcmp(type,n->data.type));

    	if(!strcmp(type,n->data.type))
    	{
    		//printf("data1: %s: %s: %ld,%ld\n", n->data.name,n->data.type,sizeof(n->data.type),sizeof(type));
    		/*
    		//Node *n = calloc(1,sizeof(Node));
			//printf("1:%s\n", data.name);
			adding.name = malloc(strlen(n->data.name) + 1);
			//printf("2:%s\n", n->data.name);
			strcpy(adding.name,n->data.name);
			printf("2:%s\n", adding.name);
			adding.hp = n->data.hp;
			printf("2:%d\n", adding.hp);
			adding.ac = n->data.ac;
			printf("2:%d\n", adding.ac);
			adding.speed = n->data.speed;
			printf("2:%d\n", adding.speed);

			n->data.type = malloc(strlen(n->data.type) + 1);
			strcpy(adding.type,n->data.type);
			*/

    		
    		TypeNode = insertNode(TypeNode,n->data);

    	}

        n = n->next;
    }

    while(TypeNode != NULL)
    {
    	printf("NAME::%s\n", TypeNode->data.name);
		printf("HP:%d\n", TypeNode->data.hp);
		printf("AC:%d\n", TypeNode->data.ac);
		printf("SPEED::%d\n", TypeNode->data.speed);
		printf("TYPE:%s\n", TypeNode->data.type);

    	TypeNode = TypeNode->next;
    }
}

void remove_newline(char *str) 
{
    int l = strlen(str);
    if (str[l - 1] == '\n') {
        str[l - 1] = 0;
    }
}