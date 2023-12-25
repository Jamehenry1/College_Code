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

float calculateMean(int rows, int cols,int matrix[rows][cols]) 
{
    if (rows <= 0 || cols <= 0) 
    {
        return 0.0;
    }

    float sum = 0.0;
    int count = 0;
    
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            sum += matrix[i][j];
            count++;
        }
    }

    return sum / count;
}

float calculateStdDev( int rows, int cols,int matrix[rows][cols]) 
{
    if (rows <= 0 || cols <= 0) 
    {
        return 0.0;
    }

    float mean = calculateMean(rows, cols,matrix);
    float sumSquaredDifferences = 0.0;
    int count = 0;

    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            float diff = matrix[i][j] - mean;
            sumSquaredDifferences += diff * diff;
            count++;
        }
    }

    float variance = sumSquaredDifferences / count;
    float stdDeviation = sqrt(variance);

    return stdDeviation;
}

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
    int tempH = roi.height;
    int tempW = roi.width;

    float CorArray[DIM][DIM] = {{0}};
    float min = 100;
    float max = -100;
    float finalMax = 0;
    int val = 0;

    int templateArr[tempW][tempH];

    // TEMPLATE ------------------------------------------------
    //  This will create the template based on the size of the 
    //      rectangle
    for (int i = 0; i < tempW; ++i) 
    {
        for (int j = 0; j < tempH; ++j) 
        {
            templateArr[i][j] = image[roi.y + i][roi.x + j];
        }
    }

    //  This will make the image to and int instead of an unsigned char
    int image2[DIM][DIM];
    for (int i = 0; i < tempW; ++i) 
    {
        for (int j = 0; j < tempH; ++j) 
        {
            image2[i][j] = image[i][j];
        }
    }
    //-----------------------------------------------------------
    

    // MEAN AND STD USED ------------------------------------------------
    //  This will get the mean and standard diviation used in the equation
    //      was not sure if we take the entire image std and mean or do we
    //      get the indivisual groups of images mean and std

    float tempMean = calculateMean(tempW,tempH,templateArr);
    float tempStd = calculateStdDev(tempW,tempH,templateArr);
    float overallImageMean = calculateMean(DIM,DIM,image2);
    float overallImageStd = calculateStdDev(DIM,DIM,image2);
    //printf("mean: %f std: %f\n", tempMean,tempStd);

    // -------------------------------------------------------------------

    for(int i = 0; i <= size[0]-tempW; i++)
    {
        for(int j = 0; j <= size[1]-tempH;j++)
        {  
            // TEMPLATE --------------------------------------------------------
            // This will create each convolution array base on the template size
            int arr[tempW][tempH];
            for(int x = 0; x < tempW; x++)
            {
                for(int y = 0; y < tempH; y++)
                {
                    int i_x = i + x;
                    int j_y = j + y;
                    arr[x][y] = image[i_x][j_y];
                    //printf("%d x = %d y = %d\n", arr[x][y],i_x,j_y);
                }
            }
            //---------------------------------------------------------------------
            float arrMean = 0;
            float arrStd = 0;

            // MEAN AND STD ??? --------------------------------------------
            //  Not completely sure if it is based on each convolution but 
            //      made it just in case

            arrMean = calculateMean(tempW,tempH,arr);
            arrStd = calculateStdDev(tempW,tempH,arr);

            //printf("arrMean: %f arrStd: %f\n", arrMean,arrStd);
            //--------------------------------------------------------------

            float imageNorm = 0;
            float tempNorm = 0;
            float nomCorVal = 0;

            // CALCULATION --------------------------------------------------------------
            //  This calculates that section of the image and normalizes it 

            for(int x = 0; x < tempW; x++)
            {
                for(int y = 0; y < tempH; y++)
                {
                    if(overallImageStd == 0)
                    {
                        imageNorm = 1;
                    }
                    else
                    {
                        //imageNorm = (arr[x][y] - arrMean)/arrStd;
                        imageNorm = (arr[x][y] - overallImageMean)/overallImageStd;
                    }
                
                    tempNorm = (templateArr[x][y] - tempMean)/tempStd;
                    nomCorVal += imageNorm * tempNorm;
                }
            }

            if(nomCorVal <= min)
            {
                min = nomCorVal;
            }
            if(nomCorVal >= max)
            {
                max = nomCorVal;
            }
            
            CorArray[i][j] = nomCorVal;
            //---------------------------------------------------------------------------
        }
    }

    // NORMALIZE THE IMAGE --------------------------------------------------
    //  This normalizes the image to be inbetween 0 and 255
    finalMax = max - min;
    for(int i = 0; i < size[0]-tempW;i++)
    {
        for(int j = 0; j < size[1]-tempH;j++)
        {   
            float minholder = CorArray[i][j] - min;
            float answer = (minholder)/(finalMax) * 255;
            proc_img[i][j] = answer;
        }

    }
    //------------------------------------------------------------------------

}