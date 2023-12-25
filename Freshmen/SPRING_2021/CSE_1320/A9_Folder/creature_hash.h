#ifndef CREATURE_HASH_H_
#define CREATURE_HASH_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXBUFFER 1028
#define LF_BOUND 0.75

typedef struct 
{
	char *name;
	char *type;
	int hp;
	int ac;
	int speed;
}Creature;

typedef struct node Node;
struct node
{
	Creature data;
	Node *next;
};

Node *addNode(Creature data);
void insertNode(Node **head, Node *new_node);

int compute_index(char *key, int array_size);
int hash_function(char *holder);
double get_load_factor(int keys, int array_size);

void remove_newline(char *str);
int traverse(Node *n, char *key);

#endif 