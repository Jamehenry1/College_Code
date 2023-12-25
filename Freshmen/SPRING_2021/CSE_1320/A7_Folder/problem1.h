#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 1028

enum priority 
{
	OPTIONAL,
	REQUIRED
};

typedef struct 
{
	char *desc;
	enum priority p;
}instructions;

typedef struct node Node;

struct node 
{
    instructions data;
    Node *next;
};

Node *addNode(instructions data);
Node *insertNode(Node *head, instructions data);
Node *removeNode(Node *head);
Node *popping(Node *head);
void traverse(Node *n);

void remove_newline(char *);