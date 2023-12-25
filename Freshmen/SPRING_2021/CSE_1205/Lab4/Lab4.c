#include <stdio.h>

int main(){
	int a = 0;
	int b =0;

	printf("a \ta==b \ta>b\n");
	while(a != 513){
		printf("%d\n", a);

		if(a<b){
			printf("\t0 \t1 \t0\n");
		}else if(a==b){
			printf("\t1 \t0 \t0\n");
		}
		else
		{
			printf("\t0 \t0 \t1\n");
		}
		a++;

	}

	return 0;
}