#include <stdio.h>
#define MAXNUMWORD 128

char * swap_and_reverse(char words[], char *key);

int main()
{

	char words[MAXNUMWORD];
	char key[MAXNUMWORD];

	printf("Enter string: ");
	fgets(words, MAXNUMWORD, stdin);
	printf("Enter key: ");
	scanf("%s", key);

	printf("%s: [%s]\n", words, key);

	char *something = swap_and_reverse(words,key);
	printf("%p\n", something);

	return 0;
}

char * swap_and_reverse(char words[], char *key)
{
	int keyLen = 0;
	int wordLen = 0;
	int diff = 0;
	int j = 0;
	int same = 0;
	char *location;

	while(key[keyLen] != '\0')
		keyLen++;
	while(words[wordLen] != '\0')
		wordLen++;

	printf("%d\n", keyLen);
	printf("%d\n", wordLen);

	/*
	compare them characters by character
	if the key appears in words word - keylen so that is starts the first instince of the word
	then move that reverse that word 
	get the address of the last letter of the word, which will now be the first letter of the word
	*/ 

	for(int i = 0; i< wordLen; i++)
	{	

		diff = words[i] - key[j];
		printf("[%d] %d = %c - %c\n",i, diff,words[i], key[j]);

		if(diff == 0)
		{
			//printf("work\n");
			same++;
			j++;

			if(same == keyLen)
			{
				printf("[%s]found ending with wordLen[%d]\n", key, i);
				location = &words[i];

				int arrLoc = i;
				int count = keyLen/2;
				int time = 0;


				printf("location: %c i = %p\n",*location,&i);

				char temp;
				
				int reverselen = i - keyLen + 1;
				printf("%d\n",reverselen);
				for(int k = 0; k < wordLen; k++)
				{
					if((k >= reverselen)&&(k < (reverselen + keyLen))&&(time < count))
					{
						temp = words[k];
						words[k] = words[arrLoc];
						words[arrLoc] = temp;
						
						arrLoc--;
						time++;
					}
				}
				printf("%s\n",words);
				

				return location;
			}

		}
		else 
		{
			j = 0;
			same = 0;
		}
	}
	
	return NULL;

}