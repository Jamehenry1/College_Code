#include "creature_list.h"
#include "utils.h"
#include "bst.h"

void dfs(BTNode *root, dfs_type t)
{
    if (root == NULL) 
    {
        return;
    }

    if (t == PREORDER) 
    {
        printf("%d\n", root->key);
        printArray(root);       
    }

    dfs(root->left, t);

    if (t == INORDER) 
    {
        printf("%d\n", root->key);
        printArray(root);       
    }

    dfs(root->right, t);

    if (t == POSTORDER) 
    {
        printf("%d\n", root->key);   
        printArray(root);       	
    }
}

void enqueue(Node **queue, BTNode *data) 
{
    if (*queue == NULL) 
    {
        *queue = calloc(1, sizeof(Node));
        (*queue)->data = data;

        return;
    }

    Node *temp = *queue;

    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = calloc(1, sizeof(Node));
    temp->next->data = data;
    //free(temp->next);
}

Node *dequeue(Node **queue) 
{
    Node *n = *queue;
    *queue = (*queue)->next;

    return n;
}

void bfs(BTNode *root) 
{
    Node *queue = NULL;
    Node *n = NULL;

    // queue up the root
    enqueue(&queue, root);

    while (queue != NULL) {
        // dequeue
        n = dequeue(&queue);
        root = n->data;
        free(n);

        // print the object
        printf("%d\n", root->key);
        printArray(root);

        // queue the subnodes
        if (root->left != NULL) {
            enqueue(&queue, root->left);
        }

        if (root->right != NULL) {
            enqueue(&queue, root->right);
        }
    } 

}

int search(BTNode *root, char *key) 
{
    Node *queue = NULL;
    Node *n = NULL;

    // queue up the root
    enqueue(&queue, root);

    while (queue != NULL) 
    {
        // dequeue
        n = dequeue(&queue);
        root = n->data;
        free(n);


        // print the object

        for(int i = 0; i < root->storageAmount; i++)
	    {
	    	
	    	if(!strcmp(key,root->data[i].name))
	    	{
	    		
	    		printf("----------------------------\n\n");
			 	printf("NAME: %-20s\n", root->data[i].name);
				printf("HP: %-20d\n", root->data[i].hp);
				printf("AC: %-20d\n", root->data[i].ac);
				printf("SPEED: %-20d\n", root->data[i].speed);
				printf("TYPE: %-20s\n", root->data[i].type);  
				printf("\n");   	
				printf("----------------------------\n\n");

	    		return 1;
	    	}
	   	}

        // queue the subnodes
        if (root->left != NULL) {
        	
            enqueue(&queue, root->left);
        }

        if (root->right != NULL) {
        
            enqueue(&queue, root->right);
        }

    }

    return 0;
}

void typeTraverse(BTNode *root, char *type)
{
	if(root == NULL)
	{
		return;
	}

	typeTraverse(root->left,type);

	for(int i = 0; i < root->storageAmount; i++)
	{
		if(!strcmp(type,root->data[i].type))
		{
			printf("----------------------------\n\n");
    	 	printf("NAME: %-20s\n", root->data[i].name);
			printf("HP: %-20d\n", root->data[i].hp);
			printf("AC: %-20d\n", root->data[i].ac);
			printf("SPEED: %-20d\n", root->data[i].speed);
			printf("TYPE: %-20s\n", root->data[i].type);  
			printf("\n");       	
			printf("----------------------------\n\n");

		}

	}

	typeTraverse(root->right,type);
}