/*
Name: Nghia Lam 
ID: 1001699317 
1)gcc lab3.c 
2)./a.out < "name of file" or ./a.out 
3)user input if used ./a.out
*/

#include <stdio.h>
#include <string.h>

float p[20];
int n;
float c[20][20];
int trace[20][20];

void tree(int left,int right,int indent)
{
	int i;
	if (left==right) // At a leaf in the optimal tree
	{
		printf("%*s%d\n",3*indent,"",left); 
		return;
	}

	tree(trace[left][right]+1,right,indent+1);   // recursive of right
	printf("%*s%d %d cost:%f \n",3*indent,"",left,right, c[left][right]); // Print the root
	tree(left,trace[left][right],indent+1);      // recursive of left
}

void bitCount(int i, int j, int key)
{
	int count = 0;
	float prob = 0;
	//printf("test: %f", p[key]);
	//printf("test: key = %d trace = %d [%d,%d]\n",key, trace[i][j], i , j);
	printf("%d ",key);
	while(i != j)
	{
		//printf("%d %s\n",trace[i][j],bit);
		if(trace[i][j] < key)
		{
			printf("1");
			i = trace[i][j] + 1;
		}
		else
		{
			printf("0");
			j = trace[i][j];
		}
		//printf("%d \n",trace[i][j]);
		count++;
	}

	prob = p[key]*count;
	printf(" %f\n",prob);

} 

int main()
{
	int i,j,k;
	float pSum = 0;
	float work;
	int r = 0;
	float totalProb = 0;


	scanf("%d",&n);
	for (i=0;i<=n;i++)
	{
			scanf("%f",&p[i]);
	}

	for(r = 0; r < n; r++)
	{
		totalProb += p[r];
	}
	printf("Probabilities sum to: %f\n",totalProb);

	for (i = 0;i <= n;i++)
	{
		 c[i][i]=trace[i][i]=0;  
	}

	for (i = 1; i < n; i++)       
	{
		for (j = 0; j <= n - i; j++)  
		{
			//printf("Compute c[%d][%d]\n",j,j+i);
			c[j][j+i]=999999;  

			for (k=j;k<j+i;k++) 
			{
				pSum = 0;
				for(r = j; r <= j + i; r++)
				{
					pSum += p[r];
				}

				work=c[j][k]+c[k+1][j+i] + pSum;
				//printf("k=%d gives cost %3f=c[%d][%d]+c[%d][%d]+p[%d]*p[%d]*p[%d]\n",k,work,j,k,k+1,j+i,j-1,k,j+i);

				if (c[j][j+i]>work)
				{
					c[j][j+i]=work;
					trace[j][j+i]=k;
				}
			}
			//printf("  c[%d][%d]==%f,trace[%d][%d]==%d\n",j,j+i,c[j][j+i],j,j+i,trace[j][j+i]);
		}
	}

	printf("   ");
	for (i = 0; i<n; i++)
	{
		printf("   %8d   ",i);
	}
	printf("\n");
	for (i=0;i<n;i++)
	{
		printf("%2d ",i);
		for ( j=0; j<n; j++)
		{
			if (i>j)
			{
				printf(" ------------ "); 
			}
			else
			{
				printf(" %3f %3d ",c[i][j],trace[i][j]);
			}
		}
		printf("\n\n");
	}

	//printf("work %d %d %d", trace[0][1],trace[0][14],trace[0][6]);
	printf("\nCode Tree\n");
	tree( 0, n-1, 0); 

	int size = n-1;
	printf("\nCodes & prob*# of bits: \n");
	for( i=0; i<n; i++)
	{
		//printf("work");
		bitCount(0,size,i);
	}
	printf("\nExpected bits per Symbol: %f\n",c[0][size]);
}
