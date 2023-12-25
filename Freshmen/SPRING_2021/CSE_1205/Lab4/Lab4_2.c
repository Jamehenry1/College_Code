#include <stdio.h>

int main(){
	int a = 0;
	int b =0;
	int time =0;

	printf("a \ta==b \ta>b\n");
	while(time < 32){
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
		
		a = (a+1)%16;
		time++;

	}

	return 0;
}