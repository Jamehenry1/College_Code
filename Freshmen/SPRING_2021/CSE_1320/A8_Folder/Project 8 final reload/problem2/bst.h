#ifndef BST_H_
#define BST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

#endif 