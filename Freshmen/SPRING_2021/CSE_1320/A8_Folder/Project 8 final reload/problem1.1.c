#include "problem1.h"


int main(int argc, char **argv)
{

	if(argc != 2)
	{
		return 1;
	}

	FILE *fp = fopen(argv[1], "r");

	int key;
	Creature holder;
	char buffer[MAXBUFFER];
	char *temp;
	int namelen;
	int typelen;
	BTNode *root = NULL;
	int choice = 0;
	dfs_type transverseType;
	


	while(1)
	{	

		fgets(buffer,MAXBUFFER,fp);

		//printf("%s\n", buffer);

		remove_newline(buffer);
		temp = strtok(buffer,",");

		//printf("---%s\n",buffer);

		
		//-------------------------------------------- Getting the monsters from file

		namelen = strlen(temp);
		holder.name = calloc((namelen + 1), sizeof(char));
		strcpy(holder.name,temp);

		//printf("Name: %s\n",holder.name);

		temp = strtok(NULL,",");
		holder.hp = atoi(temp);

		//printf("HP: %d\n", holder.hp);

		temp = strtok(NULL,",");
		holder.ac = atoi(temp);

		//printf("AC: %d\n", holder.ac);

		temp = strtok(NULL,",");
		holder.speed = atoi(temp);

		//printf("SPEED: %d\n", holder.speed);

		temp = strtok(NULL,",");
		typelen = strlen(temp);
		holder.type = calloc((typelen + 1), sizeof(char));
		strcpy(holder.type,temp);

		//printf("TYPE:%s\n",holder.type);

		key = holder.ac;

		insert(&root,key,holder);


		//free(holder.name);
		//free(holder.type);

		if(feof(fp))
		{

			break;
		}

	}	

	
	while(choice != 4)
	{
		printf("1: Traverse Tree\n");
		printf("2: Search\n");
		printf("3: Traverse by Type\n");
		printf("4: Quit\n");
		scanf("%d",&choice);
		getchar();

		switch(choice)
		{
			case 1: // DONE
			{
				printf("Select Traverse Type:\n");
				printf("1: PREORDER DFS\n");
				printf("2: INORDER DFS\n");
				printf("3: POSTORDER DFS\n");
				printf("4: BFS\n");
				scanf("%d",(int *)&transverseType);
				getchar();
				
				if(transverseType == 1)
				{
					dfs(root,PREORDER);
				}
				else if(transverseType == 2)
				{
					dfs(root,INORDER);
				}
				else if(transverseType == 3)
				{
					dfs(root,POSTORDER);
				}
				else if(transverseType == 4)
				{
					bfs(root);
				}
				
				break;
			}
			case 2: // Doing
			{

				printf("Enter Name:\n");
				fgets(buffer,MAXBUFFER,stdin);
				remove_newline(buffer);
				
				int test = search(root,buffer);
				printf("%d\n", test);
				break;
			}
			case 3:
			{
				printf("Enter type:\n");
				fgets(buffer,MAXBUFFER,stdin);
				remove_newline(buffer);

				typeTraverse(root,buffer);
				break;
			}
			case 4:
			{
				//free(temp);
				release_tree(root);
				fclose(fp);
				//free(holder.name);
				//free(holder.type);

				return 1;
				break;
			}
			default: 
				break;
		}
	}
}



BTNode *add_btnode(int key, Creature holder)
{
	//printf("work\n");
	int count = 0;
	BTNode *newNode = calloc(1,sizeof(BTNode));
	newNode->key = key;
	newNode->data = calloc(1,sizeof(Creature));
	newNode->storageAmount++;
	//count = newNode->storageAmount;

	//newNode->data[count].name = calloc((strlen(holder.name) + 1), sizeof(char));
	//newNode->data[count].type = calloc((strlen(holder.type) + 1), sizeof(char));

	newNode->data[count].name = holder.name;
	newNode->data[count].hp = holder.hp;
	newNode->data[count].ac = holder.ac;
	newNode->data[count].speed = holder.speed;
	newNode->data[count].type = holder.type;

	//free(holder.name);
	//free(holder.type);

	//printf("work2\n");
	
	return newNode;

}

void insert(BTNode **root, int key, Creature holder)
{
	BTNode **temp = root;
	int count = 0;

    while (*temp != NULL && count == 0) {
    	if (key == (*temp)->key)
    	{
    		//printf("\nlinked\n");
    		count = (*temp)->storageAmount;
    		//printf("count:{%d}\n", count);
    		(*temp)->data = realloc((*temp)->data,((*temp)->storageAmount + 1) * sizeof(Creature));
    		

    		//(*temp)->data[count].name = malloc((strlen(holder.name) + 1) * sizeof(char));
			//(*temp)->data[count].type = malloc((strlen(holder.type) + 1) * sizeof(char));

    		(*temp)->data[count].name = holder.name;
    		(*temp)->data[count].hp = holder.hp;
    		(*temp)->data[count].ac = holder.ac;
    		(*temp)->data[count].speed = holder.speed;
    		(*temp)->data[count].type = holder.type;


    		(*temp)->storageAmount++;
    		count++;

    	}
        else if (key >= (*temp)->key)
        {
        	//printf("\nright\n");
            temp = &(*temp)->right;
        } 
        else 
        {
        	//printf("\nleft\n");
            temp = &(*temp)->left;

        }

    }

    if(count == 0)
    {
    	//printf("\nadding node\n");
    	*temp = add_btnode(key,holder);
    }

    //free((*temp)->data->name);
    //free(holder.type);


}

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

void release_tree(BTNode *root) 
{
    if (root != NULL) {
        release_tree(root->left);
        release_tree(root->right);

        	
        
        for(int i = 0; i < root->storageAmount; i++)
        {
        	//free(root->data[i].name);
        	//free(root->data[i].type);
        }
        
        free(root->data);
        free(root);

        //free(root->data);
      
    }
}

void remove_newline(char *str) 
{
    int l = strlen(str);
    if (str[l - 1] == '\n') {
        str[l - 1] = 0;
    }
}
