#include <stdio.h>
#include <string.h>

#define MAXSIZE 1028

void remove_newline(char *str);
int parse_cvs(char *str);

int main()
{
	char buffer[MAXSIZE] = {0};
	int i = 0;
	int valid[9];

	fgets(buffer,MAXSIZE,stdin);
	remove_newline(buffer);
	parse_cvs(buffer);
	valid[i] = parse_cvs(buffer);
	i++;
	

	while(strcmp(buffer, "END"))
	{
		fgets(buffer, MAXSIZE, stdin);
		remove_newline(buffer);
		valid[i] = parse_cvs(buffer);
		i++;
	}

	for(int h = 0; h < i-1; h++)
	{
		printf("CSV Line[%d]: {%d}\n", h,valid[h]);
	}
	


	return 0;
}

//gets rid of the empty when using fgets
void remove_newline(char *str)
{
	int length = strlen(str);

	if(str[length - 1] == '\n')
	{
		str[length - 1] = 0;
	}
}

int parse_cvs(char *str)
{
	//printf("WORK-------\n");
	int count = 0;
	int dateTokenCount = 0;

	char *token = strtok(str, ",");

	if(token[0] != '@')
		return 1;

	//printf("%s :[0] \n", token);
	count++;

	while (token != NULL)
	{
		if(count == 1)
		{
			token = strtok(NULL, "\"");
			//printf("%s :[1] \n", token);
			count++;
		}
		else
		{
			token = strtok(NULL, ",");

			
			char *dateToken = strtok(token,"/");
			dateTokenCount++;
			//printf("%s -----> count[%d]\n ", dateToken, dateTokenCount);

			while(dateToken != NULL)
			{
				
				dateToken = strtok(NULL,"/");
				if(dateToken != NULL)
				{
					dateTokenCount++;
				}
				
				//printf("%s -----> count[%d]\n ", dateToken, dateTokenCount);

				if(dateTokenCount == 3)
					return 0;
					
			}
			if(dateTokenCount == 3)
			{
				return 0;
			}
			else
			{
				return 1;
			}

			
			//printf("%s :[2]\n", token);
			
		}
	}

	return 0;
}