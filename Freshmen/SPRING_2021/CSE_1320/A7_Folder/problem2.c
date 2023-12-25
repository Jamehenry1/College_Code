#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXBUFFER 1028

typedef struct node Node;

struct node
{
	char *data;
	Node *next;	
};

void enqueue(char buffer[],Node **head);
void dequeue(Node **head);
void print_queue(Node *head);
void remove_newline(char *);

int main()
{

	char buffer[MAXBUFFER] = { 0 };
	int choice = 0;
	
	Node *head = NULL;
	int complete = 0;

	while(choice != 3)
	{

		printf("1. Add Quest\n");
		printf("2. View Quest\n");
		printf("3. Quit\n");
		scanf("%d",&choice);
		getchar();

		switch(choice)
		{
			case 1:
				printf("Enter Quest: ");
				fgets(buffer,MAXBUFFER,stdin);
				remove_newline(buffer);

				enqueue(buffer,&head);

				//printf("%d\n", numofQuest);

				break;
			case 2:
				if(head != NULL)
				{

					print_queue(head);
					printf("1. Mark as Complete\n");
					printf("2. Go back\n");
					scanf("%d",&complete);

					if(complete == 1)
					{
						dequeue(&head);
					}
				}
				break;
			case 3:
				break;
			default:
				printf("INVALID INPUT\n");
				break;

		}

	}



	return 0;
}

void enqueue(char buffer[],Node **head)
{
	Node *new_node = calloc(1, sizeof(Node));
	new_node->data = malloc(sizeof(char) * strlen(buffer));
	strcpy(new_node->data,buffer);

	new_node->next = *head;

	*head = new_node;

}

void dequeue(Node **head)
{

	Node *temp = *head;
	Node *prev = NULL;

	while(temp->next != NULL)
	{
		prev = temp;
		temp = temp->next;
	}

	printf("-------------------------------------\n");
	printf("Quest Completed: [%s]\n", temp->data);
	printf("-------------------------------------\n");

	if(temp == *head)
	{
		*head = NULL;
	}
	else
	{
		prev->next = NULL;
	}

	free(temp);
}

void print_queue(Node *head)
{
	if(head != NULL)
	{
		while(head->next != NULL)
		{
			head = head->next;
		}

		printf("Quest: %s\n", head->data);
	}
	else
	{
		printf("No Quest Availible\n");
	}
}

void remove_newline(char *str) 
{
    int l = strlen(str);
    if (str[l - 1] == '\n') {
        str[l - 1] = 0;
    }
}