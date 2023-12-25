#ifndef BT_CREATURES_H_
#define BT_CREATURES_H_

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

// The link list that stores the data
/*
typedef struct CreaLink CreaLink;
struct CreaLink
{
	Creature data;
	CreaLink *next;
};
*/

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


// Traverse Type
typedef enum 
{
    PREORDER,
    INORDER,
    POSTORDER,
    BSF
} dfs_type;


//BFS Stuff

typedef struct Node Node;
struct Node
{
	BTNode *data;
	Node *next;
};


void enqueue(Node **,BTNode *);
Node *dequeue(Node **);
void bfs(BTNode *);
void dfs(BTNode *root, dfs_type t);
int search(BTNode *root, char *key);
void typeTraverse(BTNode *root, char *type);

//
BTNode *add_btnode(int key, Creature holder);
void insert(BTNode **root, int key, Creature holder);

void printArray(BTNode *root);
void remove_newline(char *str);
void release_tree(BTNode *root);


#endif //BT_CREATURES_H_