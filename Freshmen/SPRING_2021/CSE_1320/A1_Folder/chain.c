#include <stdio.h>
#include <string.h>

int main()
{
	char c = 0;
	int count = 0;
	int wrdI = 0;
	int wrdF = 0;

	printf("Enter your word chain: \n");

	while((c = getchar()) != '\n')
	{
		if(c == ' ')
		{
			printf("debug {%d}\n", c);	
			wrdI = count;
			count = 0;

			if(wrdF < wrdI)
			{
				wrdF = wrdI;

			}
		}
		else
			count++;
		printf("debug final {%d}:{%d}\n", count,c);	
		
	}

	printf("%d\n",wrdF);
	return 0;
}