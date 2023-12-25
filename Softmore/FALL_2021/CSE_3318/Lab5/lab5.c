/*
Name: Nghia Lam
ID: 1001699317
gcc RB.c lab4driver.c
./a.out < a.dat file
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 200

//This holds the data of the nodes
struct Node
{
    int k;      //These are the variables for the pebbles 
    int peb1;
    int peb2; 
};

//This is the edge struct
struct Edge
{
    int start;  //variables for start, end and directed
    int end;
    int dir; 
};

int main()
{
    int num, before, after;
    int i, j;

    scanf("%d", &num); //getting user input of the number of vertices
    printf("%d\n", num);

    struct Node arrNode[num];
    struct Edge arrEdge[num];
    
    //loop that initializes and take data from the struct data Edge
    for (i = 0; i < (2*num) - 3; i++)
    {
        scanf("%d", &before);
        scanf("%d", &after);

		arrEdge[i].start = before;
		arrEdge[i].end = after;
		arrEdge[i].dir = 0;

		printf("%d %d\n", before, after);
    }

    //initializes and take data from the struct of the data Node
    for (i = 0; i < num; i++)
    {
        arrNode[i].k = i;
		arrNode[i].peb1 = MAXSIZE;
		arrNode[i].peb2 = MAXSIZE;
    }
    
    //This is the peb game
    for (i = 0; i < (2*num) - 3; i++)
    {
        before = arrEdge[i].start;
		after = arrEdge[i].end;

		if (arrNode[before].peb1 == MAXSIZE && arrNode[before].peb2 == MAXSIZE)
		{
			if (arrNode[after].peb1 == MAXSIZE && arrNode[after].peb2 == MAXSIZE)
			{
				arrNode[before].peb1 = i;
				arrEdge[i].dir = 1;
			}
		}
    }

    //This checks the arraay for redundancy 
    for (i = 0; i < (2*num) - 3; i ++)
    {
        //if there is a fail edge then it will print and quit
		if (arrEdge[i].dir == 0)
		{
			printf("The last edge is redundant ");
			printf("%d,%d\n", arrEdge[i].start, arrEdge[i].end);

			exit(0);
		}
        
    }

    printf("min ridgid"); //print if test passes

    return 0;

}
