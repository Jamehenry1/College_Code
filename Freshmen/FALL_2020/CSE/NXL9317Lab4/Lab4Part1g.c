/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: nghia
 *
 * Created on December 5, 2020, 10:50 PM
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINELEN 256

// Constants for sizes
const int MAXGIFTS = 100;
const int MAXNUMS = 8;
const int MAXSTRS = 3;
const int MAXNAMELEN = 128;

// Constants for columns
const int PRICE = 0;
const int QUANT = 1;  // QUANT means quantity
const int SHIP = 2;   // SHIP means shipping
const int TAX = 3;   
const int TOTAL = 4;

const int CAT = 0;   // CAT means category
const int ITEM = 1;  // ITEM means item name

void toyFormat(char gift[MAXGIFTS][MAXSTRS][MAXNAMELEN], double details[MAXGIFTS][MAXNUMS], int row);  // after making changes below, change these names consistently with other changes
double tS(double details[MAXGIFTS][MAXNUMS], int row);   // after making changes below, change these names consistently with other changes
int bubbleSortWordInt(char gift[MAXGIFTS][MAXSTRS][MAXNAMELEN], double details[MAXGIFTS][MAXNUMS], int row);
int catCount(char gift[MAXGIFTS][MAXSTRS][MAXNAMELEN],char CATstorage[20][MAXNAMELEN], int row);
int stuffInCatCount(char gift[MAXGIFTS][MAXSTRS][MAXNAMELEN],char CATstorage[20][MAXNAMELEN],int categoryCount[20],  int row);


int main()
{
    char *fileName = "GiftList2.txt";
    FILE *gFile = fopen(fileName,"r");
    double totalCost;
    char line[MAXNAMELEN];              // replace hard coded number with appropriate constants defined above
    char gift[MAXGIFTS][MAXSTRS][MAXNAMELEN];      // choose more meaningful name for stuff; replace hard coded numbers with appropriate constants defined above
    double details[MAXGIFTS][MAXNUMS];          // choose more meaningful name for info; replace hard coded numbers with appropriate constants defined above
    int row = 0, maxRow = 0;            // choose more meaningful names for i and n; 


    // NOTE: once you change names of variables, you'll have to change them in the rest of the code
    
    // Formatting requirements:
    // Insure that code is indented consistently throughout.  Code within { } should be indented in one tab space from the {.
    // Opening { should either be consistently
    //     a) on their own line, not at the end of the previous line  OR
    //     b) at the end of the previous line
    // Each level of nested { should then indent the code inside
    
    if (gFile == NULL)
    {
    printf("%s not found\n",fileName);
    }
    else 
    {
        // Add a one line comment to explain what this while loop is doing
        
        // {    This loop is finding the total amount of rows there are in the file }
        while (!feof(gFile))
        {
            fgets(line, 256, gFile);
            maxRow++;
        }
        
        // {    Rewind sets the files position to the starting point    }
        rewind(gFile);   // What does rewind do?

        // Add a one line comment to explain what this for loop is doing
        
        //{     This loop is putting each toys' information into the 2 arrays   }
            for (row = 0; row<maxRow; row++)    {
            // In array indices, replace hard coded column numbers with appropriate constants defined above.
            fscanf(gFile, "%lf %lf %lf %lf %s %[^\n]",  
                &(details[row][0]),&(details[row][1]), &(details[row][2]), &(details[row][3]),gift[row][0], gift[row][1]); 

        }
    }
    
    double totalPrice = tS(details, row);  // Choose more meaningful name to replace t; rename function with more meaningful name
 
    toyFormat(gift, details, row);    // rename function with more meaningful name
    printf("\n%37sTotal is $%9.2lf\n"," ",totalPrice);
    
    
    char CATstorage[20][MAXNAMELEN];
    int t = catCount(gift,CATstorage,row);
    printf("\n%d categories were found\n",t);
    
    int categoryCount[20];
    
    stuffInCatCount(gift,CATstorage,categoryCount,row);
    for(int i = 0; i < 5; i++)
    {
        printf("\nCAT[%d] = %s -- Amount Inside: %d\n",i,CATstorage[i],categoryCount[i]);
    }
    
    return 0;
}

/*
 * Add brief comments to explain what the function does overall
 */

//{    This function calculates the total price of all the toys added together    }
double tS(double details[MAXGIFTS][MAXNUMS], int row)  
{
    double tPrice = 0;    // Choose more meaningful name to replace s
    double n = 0;
    for (int q = 0; q < row; q++)   // Change q to another name if desired
    {
        // In array indices, replace hard coded column numbers with appropriate constants defined above.
        details[q][4] = ( details[q][PRICE]  +  details[q][SHIP] +details[q][TAX])*details[q][QUANT];
        tPrice += details[q][4];   // What is s calculating?  What should be done with the value of s?
        //{    (tPrice) or (s) is the total price of every toy added up together    }
        //{    The value of (s) should be returned to up to totalPrice    }
    }
    n = n*2;   // What is n calculating?  What should be done with the value of n?
    // {    n does nothing so get rid of it     }
    
    return tPrice;
}

/*
 * Add brief comments to explain what the function does overall
 */

//{    This fuction formats and prints out the given data     }
void toyFormat(char gift[MAXGIFTS][MAXSTRS][MAXNAMELEN], double details[MAXGIFTS][MAXNUMS], int row)
{
    char temp[102];
    char temp2[102];
    int pos = 0;    // Choose more meaningful name to replace c
    char *gory = "Books";  // Choose more meaningful name to replace gory
    char *word;
    int linePos = 0;  // Choose more meaningful name to replace l
    printf("%12s %2s %7s   %5s     %6s       Total %4s %s\n","Category","#", "Price","Tax","Shipping"," ","Item");
    for (int p = 0; p < row; p++)
    {   
        linePos = 0;
        // In array indices below, replace hard coded numbers with appropriate constants defined above.
        
        // What does if statement do, i.e. what is it looking for?  Don't rewrite the code in English - explain it
        if (strcmp(gift[p][0],gory) == 0)
        {
            strcpy(temp2, gift[p][1]);
            word = strtok(temp2," ");
            //printf("\n{word = %s}",word);
            while (strcmp(word,"by") != 0)
            {
                linePos = linePos + strlen(word)+1;
                word = strtok(NULL," ");

            }
            // From the strcpy above to this point, what does the code do?  What does l represent at this point?
            //{    strcpy copies the string from gift[p][1] into temp2    }
            //{    The 1 represents the Col or item    }
            
            temp[0]='"';
    
            for(pos=0; (pos < linePos-1); pos++)
            {
                temp[pos+1] = gift[p][1][pos];   // Explain what this assignment is doing
                //{    replacing each the string in temp with a new one, it is doing it character by character   }
            }
            temp[pos+1] = '"';
            temp[pos+2]  =  ' ';
            for(pos = pos+1; (gift[p][1][pos] != '\0'); pos++)
            {
                temp[pos+2] = gift[p][1][pos];
            }   
            temp[pos+2] = '\0'; 
            // At this point, what is in temp compared to the former gift[p]?
            //{    if the former gift[p] is the line before this one then it would be different, however, if the former gift[p] you are talking about is on the same line then the strings would be the same    }
        }
        else
        {
            strcpy(temp,gift[p][1]);
        }
        // In array indices, replace hard coded column numbers with appropriate constants defined above.
            bubbleSortWordInt(gift,details,row);
        printf("%12s %2.0lf  $%6.2lf  $%5.2lf  $%6.2lf   =  $%8.2lf for  %s\n",
            gift[p][CAT], details[p][ITEM], details[p][PRICE], details[p][TAX], details[p][SHIP], details[p][TOTAL], gift[p][ITEM]);
    }
}

int bubbleSortWordInt(char gift[MAXGIFTS][MAXSTRS][MAXNAMELEN], double details[MAXGIFTS][MAXNUMS], int row)
{
    float temp1 = 0;
    float temp2 = 0;
    float temp3 = 0;
    float temp4 = 0;
    int temp5 = 0;
    char wordTemp[MAXNAMELEN];
    char wordTemp2[MAXNAMELEN];
    
    for (int outer = 0; outer < (row - 1); outer++)
    {
        for(int i = 0; i < ((row -1)- outer); i++)
        {
            if(strcmp(gift[i],gift[i+1]) > 0)
            {
                temp1 = details[i][TOTAL];
                details[i][TOTAL] = details[i+1][TOTAL];
                details[i+1][TOTAL] = temp1;
                
                temp2 = details[i][PRICE];
                details[i][PRICE] = details[i+1][PRICE];
                details[i+1][PRICE] = temp2;
                
                temp3 = details[i][TAX];
                details[i][TAX] = details[i+1][TAX];
                details[i+1][TAX] = temp3;
                
                temp4 = details[i][SHIP];
                details[i][SHIP] = details[i+1][SHIP];
                details[i+1][SHIP] = temp4;
                
                temp5 = details[i][QUANT];
                details[i][QUANT] = details[i+1][QUANT];
                details[i+1][QUANT] = temp5;
                
                strcpy(wordTemp,gift[i]);
                strcpy(gift[i],gift[i+1]);
                strcpy(gift[i+1],wordTemp);
                
                strcpy(wordTemp2,gift[i][1]);
                strcpy(gift[i][1],gift[i+1][1]);
                strcpy(gift[i+1][1],wordTemp2);
                
                
            }
            else if(strcmp(gift[i][CAT],gift[i+1][CAT]) == 0 && strcmp(gift[i][ITEM],gift[i+1][ITEM]) > 0)        
            {               
                temp1 = details[i][TOTAL];
                details[i][TOTAL] = details[i+1][TOTAL];
                details[i+1][TOTAL] = temp1;

                temp2 = details[i][PRICE];
                details[i][PRICE] = details[i+1][PRICE];
                details[i+1][PRICE] = temp2;

                temp3 = details[i][TAX];
                details[i][TAX] = details[i+1][TAX];
                details[i+1][TAX] = temp3;

                temp4 = details[i][SHIP];
                details[i][SHIP] = details[i+1][SHIP];
                details[i+1][SHIP] = temp4;

                temp5 = details[i][QUANT];
                details[i][QUANT] = details[i+1][QUANT];
                details[i+1][QUANT] = temp5;

                strcpy(wordTemp,gift[i]);
                strcpy(gift[i],gift[i+1]);
                strcpy(gift[i+1],wordTemp);

                strcpy(wordTemp2,gift[i][1]);
                strcpy(gift[i][1],gift[i+1][1]);
                strcpy(gift[i+1][1],wordTemp2); 
            }
        }
  
    }
}

int catCount(char gift[MAXGIFTS][MAXSTRS][MAXNAMELEN],char CATstorage[20][MAXNAMELEN], int row)
{
    char text[MAXNAMELEN];
    int t = 0;
    
    for(int k = 0; k < row; k++)
    {
        if(strcmp(gift[k][CAT],text) != 0)
        {
            strcpy(text,gift[k][CAT]);
            strcpy(CATstorage[t],text);
            printf("\nCAT[%d] = %s\n",t,CATstorage[t]);
            t++;
            
        }
    }
    return t;
}

int stuffInCatCount(char gift[MAXGIFTS][MAXSTRS][MAXNAMELEN],char CATstorage[20][MAXNAMELEN],int categoryCount[20],  int row)
{
    int count = 0;
    for(int i = 0; i < 5; i++)
    {
        
        for(int index = 0; index < row; index++)
        {
            
            if(strcmp(CATstorage[i],gift[index][CAT]) == 0)
            {
                count++;
              
            }      
        }
        categoryCount[i] = count;
        count = 0;
    }
   
}