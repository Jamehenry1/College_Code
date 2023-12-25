#include <stdio.h>

#define MAXSTRINGLEN 128

int str_to_word(char word[], char *arrWord[]);

int main()
{
	char word[MAXSTRINGLEN];
	char *arrWord[MAXSTRINGLEN];
	printf("Enter your sentence: ");
    fgets(word,MAXSTRINGLEN,stdin);

    printf("%s",word);

    int num = str_to_word(word, arrWord);

    printf("%d word(s) found\n", num);

    for(int j = 0; j < num; j++)
    {
    printf("%d = %p\n",*arrWord[j], &arrWord[j]);
	}

	return 0;
}

int str_to_word(char word[], char *arrWord[])
{
	int sentenceLen = 0;
	int numWord = 1;

	while(word[sentenceLen] != '\0')
		sentenceLen++;
	//printf("%d\n", sentenceLen);

	arrWord[0] = &word[0];

	for(int i = 0; i < sentenceLen-1; i++)
	{

		if((word[i-1] == ' ')&&(word[i] != '\0'))
		{
			if(word[i] != ' ')
			{
				arrWord[numWord] = &word[i];
				numWord++;
			}
			
		}

	}

	//printf("%c\n", *arrWord);

	return numWord;

}