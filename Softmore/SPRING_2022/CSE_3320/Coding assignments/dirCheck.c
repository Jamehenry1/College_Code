// Nghia Lam
// 1001699317
// Linix on VM
// Using C

#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

struct dirent *dir;										//Struct of what I need to read and check through the directory
struct stat path_stat;

long int Sum( char*);

int main()
{
	DIR *d;
	char* dirloc = ".";	
	int TotalSum;

	TotalSum = Sum(dirloc);
	printf("TotalSum = %d\n", TotalSum);
	return(0);
}

long int Sum( char *directoryName)
{
	//printf("New Folder\n");
	char s[1000];										//For print checking directory
	long int sum = 0;									//Sum of bytes
	int checker = 0;									//Checks if it is a file (0) or folder (1)						
	int reCount = 0;									//Count the amount of recursion 

	DIR *d;
	d = opendir(directoryName);							//This is the starting path of the directory (where the file is rn)
	
	chdir(directoryName);								//Changes my working directory to a new directory
	//printf("%s\n", getcwd(s, 1000));					

	if(d) //if there is a vaild directory
	{
		while((dir = readdir(d)) != NULL)				//If it is a directory
		{
			//printf("Name 2:%s\n", dir->d_name);
			stat(dir->d_name, &path_stat);				//Puts data of dir or file into path_stat	
			
			checker = S_ISDIR(path_stat.st_mode); 		//Checks if it is a file or a directory 0 is file
			//printf("test 1: %d\n", checker);

			if(strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)		//if the dir name is . or .. it doesnt run
			{
				//printf("Skip Skip\n");
      			continue;
			}
			 
			if(checker == 1)							//Checks to see if it is a Directory
			{
				reCount++;								//Add 1 to the number of times I have used recursion
				sum += Sum(dir->d_name);				//Does recursion

				if(reCount != 0)						//checks my recusion and change my working directory to the previous directory
				{
					reCount--;							//finished 1 recursive loop
					chdir("..");
				}		
			}
			else if(checker == 0)						//Checks to see if it is File
			{
				sum += path_stat.st_size;				//It is add the size to the total size so far
			}
		}
		closedir(d);									//closes directory
	}
	return sum;
}
