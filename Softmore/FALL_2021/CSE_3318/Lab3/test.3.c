#include <stdio.h>

float p[20];
int n;
float c[20][20];
int trace[20][20];

void tree(int left, int right, int indent)
{
    int i;

    if(left == right)
    {
        for(i=0; i < indent; i++)
        {
            printf("   ");
        }
        printf("%d\n",left);
        return;
    }

    tree(trace[left][right]+1,right,indent+1);
    for(i=0;i<indent;i++)
        printf("   ");
    printf("%d %d\n",left,right);
    tree(left,trace[left][right],indent+1);
}

int main()
{
    int i,j,k;
    float work;
    float pSum = 0;

    scanf("%d",&n);
    for (i=0;i<=n;i++)
    {
        scanf("%f",&p[i]);
    }

    for (i=1;i<=n;i++)
    {
        c[i][i]=trace[i][i]=0;
    }

    for (i=1;i<n;i++)
    {
        for (j=1;j<=n-i;j++)
        {
            //pSum = 0;
            //pSum = p[]
            printf("Compute c[%d][%d]\n",j,j+i);
            c[j][j+i]=999999;
            for (k=j;k<j+i;k++)
            {
                //pSum = 0;
                int r = 0;
                
                for(r = j; r <= j+i; r++)
                {
                    pSum += p[r];
                }
                
                //work = c[j][k] + c[k+1][j+i] + p[j-1]*p[k]*p[j+i];
                //work = c[j][k] + c[k+1][j+i] + p[j-1]*p[k]*p[j+i];
                work = c[j][k] + c[k+1][j+1] + pSum;
                printf(" k=%d gives cost %3f=c[%d][%d]+c[%d][%d]+p[%d]*p[%d]*p[%d]\n"
                    ,k,work,j,k,k+1,j+i,j-1,k,j+i);
                if (c[j][j+i]>work)
                {
                    c[j][j+i]=work;
                    trace[j][j+i]=k;
                }
            }
            printf(" c[%d][%d]==%f,trace[%d][%d]==%d\n",j,j+i,
            c[j][j+i],j,j+i,trace[j][j+i]);
        }
    }

    printf("   ");
    for(i=1;i<=n;i++)
    {
        printf("   %8d   ",i);
    }
    printf("\n");
    for (i=1;i<=n;i++)
    {
        printf("%2d ",i);
        for (j=1;j<=n;j++)
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
        printf("\n");
        printf("\n");
    }

    tree(1,n,0);
}
