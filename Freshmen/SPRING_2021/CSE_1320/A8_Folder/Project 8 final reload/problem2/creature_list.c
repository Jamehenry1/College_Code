#include "creature_list.h"
#include "utils.h"
#include "bst.h"


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
	newNode->data = calloc(1,(count + 1) * sizeof(Creature));
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
