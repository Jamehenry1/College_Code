#include <stdio.h>
#include <string.h>

#define MAXUSER 128
#define MAXLENNAME 64

int add_user(int id[],char name[][MAXLENNAME], int age[], int time);
void list_user(int id[],char name[][MAXLENNAME], int age[], int time);
int get_user(int id[],char name[][MAXLENNAME],int age[],int time,int idFind);
int find_user(char name[][MAXLENNAME], int time, char nFind[]);

int main()
{

	int user_ID[MAXUSER] = {0};
	char names[MAXUSER][MAXLENNAME];
	int ages[MAXUSER] = {0};

	int choice = 0;
	int numUser = 0;
	int test0 = 0;

	int idSort = 0;
	int value = 0;

	char nSort[MAXLENNAME];
	int strValue = 0;

	while(choice != 4)
	{

		printf("\n\tMENU\n[0]: Add User\n[1]: List All Users\n[2]: Find User by ID\n[3]: Find User by Name\n[4]: Exit\nEnter Your Choice:");
		scanf("%d",&choice);
		switch(choice)
		{

			case(0): //add a user
			{
				
				if(add_user(user_ID,names,ages,numUser) == 1)
				{
					printf("NOT ENOUGH SPACE\n");
				}
				else
				{
					printf("\nA user has been added to the Database\n");
					numUser++;
				}
				break;
			}
			case(1): //list all users
			{
				list_user(user_ID,names,ages,numUser);
				break;
			}
			case(2): //find user by id 
			{
				printf("Enter the ID that you want to find: \n");
				scanf("%d",&idSort);

				value = get_user(user_ID,names,ages,numUser,idSort);
				if(value != -1)
				{
					printf("\nID Found\n");
					printf("Name: %-15s Age: %3d\n",names[value],ages[value]);
				}
				else 
				{
					printf("There is no matching ID\n");
				}

				break;
			}
			case(3): //find users by name
			{
				printf("Enter the Name that you want to find: \n");
				scanf("%s",nSort);

				strValue = find_user(names,numUser,nSort);
				if(strValue != -1)
				{
					printf("\nName Found\n");
					printf("ID: %-10d Age: %3d\n",user_ID[strValue],ages[strValue]);
				}
				else 
				{
					printf("There is no matching Names\n");
				}

				break;
			}
			default:	
				printf("\nInvalid selection\n\n");

		}
	}

	return 0;
}

int add_user(int id[],char name[][MAXLENNAME], int age[], int time)
{
	//time is the amount of users that are already in the fuction,
	//and if time is == MAXUSER then this fuction does not run
	if(time == MAXUSER)
	{
		return 1;
	}
	else
	{
		printf("Enter your ID: ");
		scanf("%d", &id[time]);

		printf("Enter your Name: ");
		scanf("%s", name[time]);

		printf("Enter your age: ");
		scanf("%d", &age[time]);
		return 0;
	}	
}

void list_user(int id[],char name[][MAXLENNAME], int age[], int time)
{
	printf("%-3s   %-10s %15s %3s\n","#","ID","Name","Age");
	for(int i = 0; i < time;i++)
	{
		printf("[%d]   %-10d %15s %3d\n",i,id[i],name[i],age[i]);
	}
}

int get_user(int id[],char name[][MAXLENNAME],int age[],int time,int idFind)
{
	for(int i = 0; i < time; i++)
	{
		if(idFind == id[i])
		{
			return i;

		}
	}
	return -1;
}

int find_user(char name[][MAXLENNAME], int time, char nFind[])
{

	for(int i = 0; i < time; i++)
	{
		if(strcasecmp(nFind,name[i]) == 0)
		{
			return i;
		}

	}
	return -1;
}