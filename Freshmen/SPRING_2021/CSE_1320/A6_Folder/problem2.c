#include "problem2.h"

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
	strcat(head->data.type,"\n");
	while(head != NULL)
	{

		if(!strcmp(type,head->data.type))
		{
			TypeNode = insertNode(TypeNode,head->data);

		}

		head = head->next;
	}

	traverse(TypeNode);

	free(TypeNode);
	free(head);

	return 0;
}

Node *addNode(Creature data)
{
	Node *n = calloc(1,sizeof(Node));

	n->data.name = malloc(strlen(data.name) + 1);
	strcpy(n->data.name,data.name);
	n->data.hp = data.hp;
	n->data.ac = data.ac;
	n->data.speed = data.speed;
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

void traverse(Node *n) {

    while (n != NULL)
    {
		printf("NAME::%s\n", n->data.name);
		printf("HP:%d\n", n->data.hp);
		printf("AC:%d\n", n->data.ac);
		printf("SPEED::%d\n", n->data.speed);
		printf("TYPE:%s\n", n->data.type);

		n = n->next;
    }

    
}

void remove_newline(char *str) 
{
    int l = strlen(str);
    if (str[l - 1] == '\n') {
        str[l - 1] = 0;
    }
}