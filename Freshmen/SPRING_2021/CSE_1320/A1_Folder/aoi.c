#include <stdio.h>

// This calculates the domain and range of the rectangles 
void calculate(int x, int y, int w, int h, int row,int rArray[2][4]);

int main()
{
	int x1,y1,w1,h1 = 0;
	int x2,y2,w2,h2 = 0;

	int rA[2][4]; // Will hold domain and range both rectagles information
	

	printf("Input data for rectangle 1 (x y width height):");
	scanf("%d %d %d %d", &x1, &y1, &w1, &h1);
	printf("Input data for rectangle 2 (x y width height):");
	scanf("%d %d %d %d", &x2, &y2, &w2, &h2);

	calculate(x1,y1,w1,h1,0,rA);
	calculate(x2,y2,w2,h2,1,rA);


	printf("Rectangle 1: %d %d %d %d\n",x1,y1,w1,h1);
	printf("Rectangle 2: %d %d %d %d\n",x2,y2,w2,h2);

	// This shows the domain and range of rectangle 1 and rectangle 2
	//printf("\nDomain 1: {%2d %2d } Range 1: {%2d %2d }\n",rA[0][0], rA[0][1], rA[0][2], rA[0][3]);
	//printf("\nDomain 2: {%2d %2d } Range 2: {%2d %2d }\n",rA[1][0], rA[1][1], rA[1][2], rA[1][3]);

    // This compares the domain and range of the 2 rectangles to see if there is a collision or not
    // This logic though :) 
	if( (((rA[0][0] >= rA[1][0])&&(rA[0][0] <= rA[1][1])) || ((rA[0][1] >= rA[1][0])&&(rA[0][1] <= rA[1][1]))) ||
		(((rA[1][0] >= rA[0][0])&&(rA[1][0] <= rA[0][1])) || ((rA[1][1] >= rA[0][0])&&(rA[1][1] <= rA[0][1]))) )
	{
		if( (((rA[0][2] >= rA[1][2])&&(rA[0][2] <= rA[1][3])) || ((rA[0][3] >= rA[1][2])&&(rA[0][3] <= rA[1][3]))) ||
		    (((rA[1][2] >= rA[0][2])&&(rA[1][2] <= rA[0][3])) || ((rA[1][3] >= rA[0][2])&&(rA[1][3] <= rA[0][3]))) )
		{
			printf("Collision detected!\n");
		}

	}
	else
		printf("No collision.\n");

	return 0;
}

void calculate(int x, int y, int w, int h, int row, int rArray[2][4])
{

	rArray[row][0] = x - (w/2);
	rArray[row][1] = x + (w/2);
	rArray[row][2] = y - (h/2);
	rArray[row][3] = y + (h/2); 

}
	