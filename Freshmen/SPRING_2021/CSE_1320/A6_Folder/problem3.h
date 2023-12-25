#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSTRING 1280



typedef struct
{
	int hp;
	int ac;
	int speed;
	char *name;
	char *type;
} Creature;

typedef struct node Node;

struct node {
    Creature data;
    Node *next;
};

Node *addNode(Creature data);
Node *insertNode(Node *head, Creature data);
void traverse(Node *n,char *type,Node *TypeNode);
void remove_newline(char *);
