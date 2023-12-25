#ifndef CREATURE_LIST_H_
#define CREATURE_LIST_H_

#define MAXBUFFER 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// Where the CSV data is stored
typedef struct
{
	char *name;
	char *type;
	int hp;
	int ac;
	int speed;
} Creature;

// The binary tree
typedef struct BTNode BTNode;
struct BTNode 
{
	int key;
	int storageAmount;
	Creature *data;
	BTNode *left;
	BTNode *right;	
};



BTNode *add_btnode(int key, Creature holder);
void insert(BTNode **root, int key, Creature holder);




#endif 