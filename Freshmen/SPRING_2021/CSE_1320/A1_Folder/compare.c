#include <stdio.h>

int stringLen(char str[]);  // this fuction gets the strings length

int main()
{
	int strcmp(char[],char[]);
	int constant = 100;
	int same = 0;

	char str1[constant];
	char str2[constant];

	printf("Enter 1st string: ");
	scanf("%s",str1);
	printf("Enter 2st string: ");
	scanf("%s",str2);

	printf("String1: %s  | String2: %s\n",str1,str2);

	int len1 = stringLen(str1);
	int len2 = stringLen(str2);

	printf("1:%d 2:%d\n",len1,len2);
	
	if(len1 != len2)
	{
		
		printf("return 2\n");
		return 2; // this value shows the strings are not equal to each other

	}
	else 
	{
		// compares each characters' ASCII values to each other
		for(int i = 0; i < len1; i++)
		{
			int diff = str1[i] - str2[i];
			//printf("test %d:%d",i,diff);

			if(diff == 0)
			{
				same++;
				printf("test: %d:%d\n", same,len1);

				if(same == len1)
				{
					printf("return 0\n");
					return 0;
				}
				
			}
		
			else if(diff != 0 && diff != 32 && diff != -32)
			{
				printf("return 2\n");
				return 2; // this value shows the strings are not equal to each other
			}
			diff = 0;

		}
		printf("return 1\n");
		return 1; // this value shows the strings are equal but cases don't all match
	}
	

	return 0;
}


int stringLen(char str[])
{
	int i = 0;
	while(str[i] != '\0')
		i++;

	return i;

}

/* NOTES: 
	strcmp only compares until the first different character then it stops
	can't use string.h; therefore can't use strcmp (would have made it easier)
						can't use strlen

	Can't beleive this took me 2 hours
	I was fun to be honest (only when I finished)
*/