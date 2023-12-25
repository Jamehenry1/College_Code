#include "problem1.h"

int main()
{

	int choice = 0;
	char buffer[BUFFER];
	//char *holder;
	instructions temp;
	instructions *test = malloc(sizeof(test));
	Node *head = NULL;
	enum priority priorityCheck;

	while (choice != 4)
	{
		
		printf("1. Add step\n");
		printf("2. Undo step\n");
		printf("3. Assemble\n");
		printf("4. Quit\n");
		scanf("%d",&choice);
		getchar();

		switch (choice)
		{
			case 1:
				printf("Description: ");
				fgets(buffer,BUFFER,stdin);
				remove_newline(buffer);
				printf("Priority (0, 1): ");
				scanf("%d", (int *)&priorityCheck);
				temp.desc = malloc((strlen(buffer) + 1) * sizeof(char));

				strcpy(temp.desc,buffer);
				temp.p = priorityCheck;
				
				/*
				if(temp.p == OPTIONAL)
				{
					printf("OPTIONAL\n");
				}
				else if(temp.p == REQUIRED)
				{
					printf("REQUIRED\n");
				}
			    */

				//printf("%s\n", temp.desc);

				head = insertNode(head,temp);

				//printf("%s\n", head->data.desc);
				//add step
				break;
			case 2:

				head = removeNode(head);
				
				//undo step
				break;
			case 3:
				head = popping(head);
				//assemble
				break;
			case 4:
				//quit
				break;
			default: 
				printf("INVALID CHOICE");
				break;
		}

		//traverse(head);
	}

	free(temp.desc);

	return	0;

}

Node *addNode(instructions data)
{
	Node *n = calloc(1,sizeof(Node));
	n->data.desc = malloc((strlen(data.desc) + 1) * sizeof(char));
	strcpy(n->data.desc,data.desc);
	n->data.p = data.p;

	//printf("In Addnode: %s\n", n->data.desc);

	return n;
}

Node *insertNode(Node *head, instructions data)
{
	Node *newNode = addNode(data);

	newNode->next = head;

	return newNode;
}

Node *removeNode(Node *head)
{
	if(head != NULL)
	{
		char popdata[BUFFER];
		strcpy(popdata,head->data.desc);
		Node *current = head;

		printf("Step \"%s\" removed\n\n", popdata);
		
		head = current->next;
		free(current);
	}
	else
	{
		printf("No more instructions\n\n");
	}

	return head;
}


Node *popping(Node *head)
{
	int count = 1;
	while(head != NULL)
	{
		char popdata[BUFFER];
		strcpy(popdata,head->data.desc);
		Node *current = head;

		if(current->data.p == REQUIRED)
		{
			printf("%d: %s\n",count, popdata);
			count++;
		}
		
		head = current->next;
		free(current);
	}

	return head;
}

void traverse(Node *n) 
{
    while (n != NULL) 
    {
    	if(n->data.p == REQUIRED)
    	{
	        printf("data: %s\n", n->data.desc);
	        n = n->next;
    	}
    }
}


void remove_newline(char *str) 
{
    int l = strlen(str);
    if (str[l - 1] == '\n') {
        str[l - 1] = 0;
    }
}