#include "creature_list.h"
#include "utils.h"
#include "bst.h"

void remove_newline(char *str) 
{
    int l = strlen(str);
    if (str[l - 1] == '\n') {
        str[l - 1] = 0;
    }
}

void release_tree(BTNode *root) 
{
    if (root != NULL) {
        release_tree(root->left);
        release_tree(root->right);

        	
        
        for(int i = 0; i < root->storageAmount; i++)
        {
        	free(root->data[i].name);
        	free(root->data[i].type);
        }
        
        free(root->data);
        free(root);

        //free(root->data);
      
    }
}

void printArray(BTNode *root)
{

    printf("----------------------------\n\n");
     for(int i = 0; i < root->storageAmount; i++)
        {
            printf("NAME: %-20s\n", root->data[i].name);
            printf("HP: %-20d\n", root->data[i].hp);
            printf("AC: %-20d\n", root->data[i].ac);
            printf("SPEED: %-20d\n", root->data[i].speed);
            printf("TYPE: %-20s\n", root->data[i].type);  
            printf("\n");   
        }
    printf("----------------------------\n\n");
}