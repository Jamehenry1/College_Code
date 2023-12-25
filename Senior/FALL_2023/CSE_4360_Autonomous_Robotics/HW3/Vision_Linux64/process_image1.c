#include <stdio.h>
#include <math.h>
#include <X11/Xlib.h>

#define DIM 512

/******************************************************************/
/* This structure contains the coordinates of a box drawn with    */
/* the left mouse button on the image window.                     */
/* roi.x , roi.y  - left upper corner's coordinates               */
/* roi.width , roi.height - width and height of the box           */
/******************************************************************/
extern XRectangle roi;

int ver[3][3] = {{-1,0,1},
                {-2,0,2},
                {-1,0,1}};

int hor[3][3] = {{-1,-2,-1},
                {0,0,0},
                {1,2,1}};
        
int majDiag[3][3] = {{0,-1,-2},
                {1,0,-0},
                {2,1,0}};
            
int minDiag[3][3] = {{-2,-1,0},
                {-1,0,1},
                {0,1,2}};

/******************************************************************/
/* Main processing routine. This is called upon pressing the      */
/* Process button of the interface.                               */
/* image  - the original greyscale image                          */
/* size   - the actual size of the image                          */
/* proc_image - the image representation resulting from the       */
/*              processing. This will be displayed upon return    */
/*              from this function.                               */
/******************************************************************/
void process_image(image, size, proc_img)
unsigned char image[DIM][DIM];
int size[2];
unsigned char proc_img[DIM][DIM];
{
    
    int dotArray[DIM][DIM] = {{0}};
    int min = 0;
    int max = 0;
    float finalMax = 0;

    for(int i = 0; i <= size[0]-2; i++)
    {
        for(int j = 0; j <= size[1]-2;j++)
        {
            // TEMPLATE --------------------------------------------------------
            //  This will create each convolution array base on the template size
            int arr[3][3] = {{0}};
            for(int x = 0; x < 3; x++)
            {
                for(int y = 0; y < 3; y++)
                {
                    int i_x = i + x;
                    int j_y = j + y;
                    arr[x][y] = image[i_x][j_y];
                }
            }
            //------------------------------------------------------------------

            // CALCULATION --------------------------------------------------------------
            //  This calculates that section of the image based on with SOBEL template it
            //      is using 
            int dotProductSum = 0;
            for(int x = 0; x < 3; x++)
            {
                for(int y = 0; y < 3; y++)
                {
                    // dotProductSum += ver[x][y] * arr[x][y];
                    // dotProductSum += hor[x][y] * arr[x][y];
                    // dotProductSum += majDiag[x][y] * arr[x][y];
                    dotProductSum += minDiag[x][y] * arr[x][y];
                }
            }  

            dotArray[i][j] = dotProductSum;

            if(dotProductSum <= min)
            {
                min = dotProductSum;
            }
            if(dotProductSum >= max)
            {
                max = dotProductSum;
            }
            
        }
       
    }


    // NORMALIZE THE IMAGE --------------------------------------------------
    //  This normalizes the image to be inbetween 0 and 255

    finalMax = max - min;
    int MAXSIZE = DIM-2;
    float temp[MAXSIZE][MAXSIZE]; // Declare the VLA
   
    for(int i = 0; i < size[0]-2;i++)
    {
        for(int j = 0; j < size[1]-2;j++)
        {   
            float minholder = dotArray[i][j] - min;
            float answer = (minholder)/(finalMax) * 255;
            temp[i][j] = answer;
        }
    }

    for(int i = 0; i < size[0]-2;i++)
    {
        for(int j = 0; j < size[1]-2;j++)
        {   
            proc_img[i][j] = temp[i][j];
        }
    }
    //------------------------------------------------------------------------
    
}


