#include "creature_hash.h"

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		return 1;
	}

	FILE *fp = fopen(argv[1], "r");

	int mapsize = 4;
	int num_keys = 0;
	Node **hash_map = NULL;

	hash_map = calloc(mapsize, sizeof(Node));
	//Node *hash_map[mapsize];

	//printf("work\n");
	//if(hash_map[1] == NULL)
	//{
	//	printf("IT is NULL\n");
	//}

	
	Creature holder;
	char buffer[MAXBUFFER];
	char *temp = NULL;
	int namelen = 0;
	int typelen = 0;
	
	int choice = 0;
	int index = 0;
	
	char *searchName = NULL;

	Node **new_map = NULL;
	Node *newnode = NULL;

	while(1)
	{	

		if(feof(fp))
		{

			break;
		}

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


		double currentLoad = get_load_factor(num_keys,mapsize);
		double newLoad = get_load_factor(num_keys + 1, mapsize);

		
		printf("Current Load: %.2lf\n", currentLoad);
		printf("New Load: %.2lf\n", newLoad);
		
		if(newLoad > LF_BOUND)
		{
			//need to rehash
			int new_size = mapsize * 3;
			
			new_map = calloc(new_size,sizeof(Node));

			printf("Rehashing\n");
			//printf("------%s\n", hash_map[0]->data.name);

			for(int  i = 0; i < mapsize; i++)
			{
				Node *temp = hash_map[i];

				//printf("work[%d]\n", i);

				//if(temp == NULL)
				//{
				//	continue;
				//}
				//if(temp != NULL)
				//{
				//printf("------%s\n", temp->data.name);
				while(temp != NULL)
				{
					//printf("------%s\n", temp->data.name);
					//printf("------%s\n", temp->data.type);
					int new_index = compute_index(temp->data.name, new_size);
					insertNode(&new_map[new_index],temp);
					//if(temp->next != NULL)
					//{
					temp = temp->next;
					//}
				}
				//}
			}	

			free(hash_map);
			hash_map = new_map;

		    //free(new_map);
			//new_map = NULL;

			mapsize = new_size;
			
			//printf("SIZE[%d]\n", mapsize);
		}

		//putting into a node
		newnode = addNode(holder);
		//printf("%s\n", newnode->data.name);

		//finding the index
		index = compute_index(holder.name,mapsize);

		//putting in the map
		insertNode(&hash_map[index],newnode);

		free(holder.name);
		holder.name = NULL;
		free(holder.type);
		holder.type = NULL;

		if(newnode != NULL)
		{
			//free(newnode);
			//newnode = NULL;
		}

		num_keys++;
	}	

	if(new_map != NULL)
	{
		free(new_map);
	}

	if(newnode != NULL)
	{
		//free(newnode);
		//newnode = NULL;
	}
	
	//free(newnode);
	//newnode = NULL;
	
	int check;

	while(choice != 3)
	{
		printf("1: Search\n");
		printf("2: Add Creature\n");
		printf("3: Quit\n");
		scanf("%d",&choice);
		getchar();

		switch(choice)
		{
			case 1:
			{
				printf("Enter name: ");
				fgets(buffer,MAXBUFFER,stdin);
				remove_newline(buffer);
				searchName = calloc(strlen(buffer) + 1,sizeof(char));
				strcpy(searchName,buffer);

				index = compute_index(searchName,mapsize);
				printf("index: %d\n", index);
				check = traverse(hash_map[index],searchName);
				if(check == 0)
				{
					printf("Does not exsist\n");
				}


				break;
			}
			case 2:
			{
				printf("Enter Name: ");
				fgets(buffer,MAXBUFFER,stdin);
				remove_newline(buffer);

				holder.name = calloc(strlen(buffer) + 1, sizeof(char));
				strcpy(holder.name, buffer);

				printf("Enter Type: ");
				fgets(buffer,MAXBUFFER,stdin);
				remove_newline(buffer);

				holder.type = calloc(strlen(buffer) + 1, sizeof(char));
				strcpy(holder.type, buffer);

				printf("Enter HP: ");
				scanf("%d",&holder.hp);
				printf("Enter AC:");
				scanf("%d",&holder.ac);
				printf("Enter SPEED:");
				scanf("%d",&holder.speed);
				//getchar();

				//printf("%s\n", holder.name);
				//printf("%s\n", holder.type);
				//printf("%d\n", holder.ac);
				double currentLoad = get_load_factor(num_keys,mapsize);
				double newLoad = get_load_factor(num_keys + 1, mapsize);

				
				printf("Current Load: %.2lf\n", currentLoad);
				printf("New Load: %.2lf\n", newLoad);
				
				if(newLoad > LF_BOUND)
				{
					//need to rehash
					int new_size = mapsize * 3;
					Node **new_map = calloc(new_size,sizeof(Node));

					printf("Rehashing\n");
					//printf("------%s\n", hash_map[0]->data.name);

					for(int  i = 0; i < mapsize; i++)
					{
						Node *temp = hash_map[i];

						printf("work[%d]\n", i);

						//if(temp == NULL)
						//{
						//	continue;
						//}
						//if(temp != NULL)
						//{
						//printf("------%s\n", temp->data.name);
						while(temp != NULL)
						{
							//printf("------%s\n", temp->data.name);
							//printf("------%s\n", temp->data.type);
							int new_index = compute_index(temp->data.name, new_size);
							insertNode(&new_map[new_index],temp);
							//if(temp->next != NULL)
							//{
							temp = temp->next;
							//}
							
						}
						//}

					}	

					free(hash_map);
					hash_map = new_map;
					mapsize = new_size;

					//printf("SIZE[%d]\n", mapsize);
				}

				//putting into a node
				newnode = addNode(holder);
				//printf("%s\n", newnode->data.name);

				//finding the index
				index = compute_index(holder.name,mapsize);

				//putting in the map
				insertNode(&hash_map[index],newnode);
				printf("%s added at index %d\n",holder.name,index);

				free(holder.name);
				holder.name = NULL;
				free(holder.type);
				holder.type = NULL;


				num_keys++;



				break;
			}
			case 3: 
			{
				fclose(fp);
				free(newnode);
				free(hash_map);
				if(searchName != NULL)
				{
					free(searchName);
				}
				
				return 1;
			}
			default:
			{
				break;
			}
		}	
	}

	
}

Node *addNode(Creature data)
{
	Node *n = calloc(1,sizeof(Node));
	//printf("1:%s\n", data.name);
	n->data.name = calloc(strlen(data.name) + 1, sizeof(char));
	//printf("2:%s\n", n->data.name);
	strcpy(n->data.name,data.name);
	//printf("2:%s\n", n->data.name);
	n->data.hp = data.hp;
	//printf("2:%d\n", n->data.hp);
	n->data.ac = data.ac;
	//printf("2:%d\n", n->data.ac);
	n->data.speed = data.speed;
	//printf("2:%d\n", n->data.speed);

	n->data.type = calloc(strlen(data.type) + 1, sizeof(char));
	strcpy(n->data.type,data.type);

	return n;

}

void insertNode(Node **head, Node *new_node) 
{

    if (*head == NULL) 
    {
        *head = new_node;
        //printf("Work\n");
    } 
    else 
    {
        Node *temp = *head;

        while (temp->next != NULL) 
        {
            temp = temp->next;
        }

        temp->next = new_node;
    }
}

int hash_function(char *holder)
{
	//printf("Key: %s\n", holder);

	int sum = 0;
	for(int i = 0; i < strlen(holder); i++)
	{
		sum += holder[i];
	}

	//printf("hash: %d\n", sum);
	return sum;
}

int compute_index(char *key, int array_size) 
{
    int hash = hash_function(key);
    int index = hash % array_size;

    //printf("index = %d\n", index);

    return index;
}

double get_load_factor(int keys, int array_size)
{
	return (double)keys/array_size;
}

void remove_newline(char *str) 
{
    int l = strlen(str);
    if (str[l - 1] == '\n') {
        str[l - 1] = 0;
    }
}

int traverse(Node *n, char *key) 
{
	if (n != NULL ) 
	{
		if(strcmp(n->data.name,key) == 0)
		{
			printf("(%s %s)\n", n->data.name, n->data.type);
			printf("AC: %d\nHP: %d\nSpeed: %d\n",n->data.ac, n->data.hp,n->data.speed);
			return 1;
		}
	    //printf("(%s %s)\n", n->data.name, n->data.type);
	    traverse(n->next, key);
	}
	else
	{
		return 0;
	}
	return 0;
}

