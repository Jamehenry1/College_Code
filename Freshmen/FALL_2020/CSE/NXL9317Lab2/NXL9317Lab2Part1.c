/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: nghia
 *
 * Created on October 3, 2020, 5:09 PM
 * 
 * Name: Nghia Huynh Lam
 * UTA ID: 1001699317
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int checkDate(int day, int month, int year);
int checkLeap(int yr);
void printAmerDate( int day, int month, int year);
void printEuroDate( int day, int month, int year);
void printISODate( int day, int month, int year);
void blankLn(void);
void blankLns(int n);
int addYear(int year);
int priorMonthDays(int month, int year);
void printDateAEI(int day, int month, int year);



// Add any new function declaration headers below this comment

/*
 * Lab 2 Part 1: Calculating the number of days in between two dates
 */

int main(int argc, char** argv)
{
    // Do not change any of the given code in main 
    // Add your new code after the comment marked with *** 
    int day, month, year;
    int valid = 1;    // used as a boolean flag   
    int format = 0;
    
    int currentday, currentmonth, currentyear;
    
    printf("Wlecome to the date calculation program");
    blankLns(2);
    
    // From https://www.techiedelight.com/print-current-date-and-time-in-c/    
        // time_t is arithmetic time type declared in header file time.h        
        time_t now;     
        
        // Obtain current time      
        // time() returns the current time of the system as a time_t value 
        time(&now);      
        // Convert to local time format and print to stdout    
        //printf("Today is : %s", ctime(&now));
        // localtime converts a time_t value to calendar time and    
        // returns a pointer to a tm structure with its members     
        // filled with the corresponding values    
        struct tm *local = localtime(&now); 
        
        currentday = local->tm_mday;            
        // get day of month (1 to 31)       
        currentmonth = local->tm_mon + 1;     
        // get month of year (0 to 11)      
        currentyear = local->tm_year + 1900;   
        // get year since 1900         
        printf("Today is : ");        
        printAmerDate(currentday, currentmonth, currentyear);     
        blankLns(2);
        
        //End section from https://www.techiedelight.com/print-current-date-and-time-in-c/ 
        printf("Please enter three numbers separated by spaces \nthat represent the day, the month, and \nthe year (4 digits) of your birth: ");    scanf("%d %d %d",&day, &month, &year);    valid = checkDate(day, month, year);  
        if (valid)   
        {       
            printDateAEI(day, month, year);  
        }   
        else  
        {       
            printf("\nYour input date was invalid and cannot be printed\n"); 
        }  
        
        blankLn();
        
        /*    
         // if date is valid, determine number of days between current date and input
         date  
         //      
         *  Algorithm:     
         * Calculate the remaining days in the preceding year. In other words,       
         * calculate the difference of y1-m1-d1 until y1-12-31.     
         * Count the whole years between both dates and get the number of days.     
         * Calculate the outstanding days in the subsequent year. 
         *         
         * date---| | | | | |---today
         * 
         * */
        
        // Calculate from a date to Dec 31 of same year     
        // Find out how many days from Jan 1 to current date and subtract from 365/366
        
        int sum = priorMonthDays(month, year) + day; // from user's input date
        //printf("From Jan 1 to your given date of that year is %d days\n",sum)
        
        if(currentyear > year)
        {
            sum = addYear(year) - sum;
        }
        
        //printf("From your given date to Dec 31 of that year is %d days\n",sum)
        //At this point sum has the number of days from given date to Dec 31 of given year
        
        //To get the sum of the days in the intervening years, there are multiple approaches:
            
            //1) Subtract current year minus given year * 365 + extra Feb 29s that are in between
            //2) Loop from given year to current year and add correct 365/366 for each year
            //3) ??
        
        int countYr = year +1;
        while (countYr < currentyear)
        {
            sum += addYear(countYr);
            //printf("Added year %d/n",countYr);
            //printf("sum = %d\n", sum);
            countYr++;
        }
        
        int thisYear = priorMonthDays(currentmonth,currentyear) + currentday;
        //printf("From Jan 1 to the current date of this year is %d days\n",thisYear);
        
        if(currentyear == year)
        {
            sum = thisYear - sum;
        }
        else
        {
            sum = sum + thisYear;
        }
        printf("\nThe number of days from the entered date to the current date is %d\n\n", sum);
        
        // *** START THE LAB2 MAIN FUNCTION CODE THAT YOU ARE ADDING HERE ***
        
        //1.b) CODE
        int roundedSum = (sum + 500);  
            //This adds 500 to the number so that when it turns into a decimal
        roundedSum = roundedSum / 1000;
            //Then it turns it into a decimal so that only the 1000s place wouldn't get turned to 0
        roundedSum = roundedSum * 1000;    
            //This turns it back to its original number but rounded high or low
        printf("\nThe rounded number of the sum is %d\n",roundedSum);
        
        //1.c) CODE
        int leapYr = checkLeap(year);
        if(leapYr == 1)
            printf("\nThe given year was in a leap year\n");
        else
            printf("\nThe given year wasn't in a leap year\n");
        
        //1.d) CODE
        int birthday = 0;
        
        if(currentmonth > month)
        {
            printf("\nCongratulations your birthday has already happened this year\n");
            birthday = 1;
        }
        else if ((currentmonth == month) && (currentday >= day))
        {  
            printf("\nCongratulations your birthday has already happened this year\n");  
            birthday = 1;
        }
        else
        {
            printf("\nYour birthday has not happened yet\n");     
        }
        
        //1.e) CODE
        int age = currentyear - year;
        
        printf("\nbDay = %d\n",birthday);
        if(birthday == 1)
        { 
            printf("\nYour age is %d\n",age);
        }
        else
        {
            age = age -1;
            printf("\nYour age is %d\n",age);
        }
        
        //1.f) CODE
        
        switch(1)
        {
            case 1:
                if(age >= 18)
                    printf("\nYou are eligible to vote");

            case 2:
                if(age >= 21)
                    printf("\nYou are eligible to drink in the US");

            case 3:
                if(age >= 62)
                    printf("\nYou are eligible for US Social Security");
               
            case 4:
                if(age >= 35)
                    printf("\nYou are eligible to be the President of the US");
                
            case 5:  
                if(age >= 30)
                    printf("\nYou are eligible to be Governor of Texas");
                
            case 6:
                if(age >= 16)
                    printf("\nYou are eligible to get a full time job");

            case 7:
                if(age >= 3)
                    printf("\nYou are eligible to go to school");
              
        }
       
    return (EXIT_SUCCESS);
}

// *** PUT YOUR NEW FUNCTION(S) FOR LAB2 HERE AFTER MAIN ***
// Don't forget to put your function declaration header(s) up before main





// ALL FUNCTIONS BELOW HERE SHOULD BE THE FUNCTIONS GIVEN BY DR T.
// DO NOT CHANGE ANY OF THE GIVEN FUNCTIONS BELOW 
// BUT YOU CAN ADD SIMILAR FUNCTIONS ABOVE IF NEEDED

int addYear(int year)
{
    if (checkLeap(year) == 1)
        return 366;
    else
        return 365;
}

int priorMonthDays(int month, int year)
{
    // days in whole months
    int sum = 0;
    switch (month-1)
    {
        case 11:
            sum = sum + 30;
        case 10: 
            sum = sum + 31;
        case 9:
            sum = sum + 30;
        case 8:
            sum = sum + 31;
        case 7:
            sum += 31;
        case 6:
            sum += 30;
        case 5:
            sum += 31;
        case 4:
            sum += 30;
        case 3:
            sum += 31;
        case 2:
        {
            if (checkLeap(year) == 1) // checks user input year
                sum += 29;
            else
                sum += 28;
        }
        case 1: 
            sum += 31;    
    }
    // sum will be all the days in the months PRIOR to the current month in this year
    return sum;
            
}

void printDateAEI(int day, int month, int year)
{
    int format = 1;
    blankLn();
    printf("What format would you like your output?\n    1 = American, 2 = European, 3 = ISO\n Enter the number for your format: \n");
    scanf("%d", &format);
    switch(format)
    {
        case 1:
        {
            //print date in American format   7/4/2000
            printf("Your date in American format is ");
            printAmerDate( day, month, year);
            blankLn();      
            break;
        }
        case 2:
        {
            //print date in European format 
            printf("Your date in European format is ");
            blankLn();
            break;
        }
        case 3:
        {
            //print date in ISO format 
            printf("Your date in ISO format is ");
            printISODate(day, month, year);
            blankLn();
            break;
        }
        default:
        {
            printf("Your format choice was not valid \nbut your");
            printf(" date in American format is ");
            printAmerDate( day, month, year);
            blankLn();
            break;
        }
    }
}

void blankLn(void)
{
    printf("\n");
}

void blankLns(int n)
{
    for (int k = 0; k < n; k++)
        printf("\n");
}

int checkDate(int day, int month, int year)
{
    int dateValid = 1;  // daateValid will keep track of errors; 0 value indicates error
    int yearLeap = 0;   // yearLeap == 0 for non-leap year and 1 fo leap year
    
    if ((year < 1000) || (year > 9999))
    {
        printf("\nError: Year is out of 4 digit range\n");
        dateValid = 0;
    }
    if ((month < 1) || (month > 12))
    {
        printf("\nError: Month is out of valid range\n");
    }
    if ((day < 1) || (day >31))
    {
        printf("\nError: Day is out of valid range\n");
        dateValid = 0;
    }
    
    /*
     * At this point, if dataValid == 0, then there is an error
     * Therefore, we only want to continue if there are no errors
     * At this point, we now need to check if days and months are valid with each other 
     * For example, we can't have Sept 31 or Feb 30
     */
    
    if(dateValid) // this is equivalent to saying (dateValid == 1)
    {
        if(((month == 4) || (month == 6) || (month == 9) || (month == 11)) && (day > 30))
        {
            printf("\nError: Day is out of range for given month with 30 years\n");
            dateValid = 0;
        }       
        else if (month == 2)
        {
            if(checkLeap(year) == yearLeap) // if it is NOT equal to a leap year (yearLeap == 0 means NOT a leap year)
            {
                if(day > 28)
                {
                    printf("\nError: Day is out of range for given month and year\n");
                    dateValid = 0;
                }
            }
            else   // it is a leap year
                if(day >29)
                {
                    printf("\nError: Day is out of range for given month and leap year \n");
                    dateValid = 0;
                }
        }     
    }
     return dateValid;
}

int checkLeap(int yr)
{
    /*
     * A year is a leap year if it is divisible by 4 and NOT divisibel by 100 UNLESS it is divisible by 400
     */
    int leap = 0;
    /*
     * 5 % 4 = 1, 21 % 4 = 1
     * 7 % 4 = 3
     * 4 % 4 = 0, 2020 % 4 = 0     
     * 6 % 4 = 2, 10 % 4 = 2
     */
    if((yr % 4) != 0) // yr % 4 - has possible answers of ? 0,1,2,3
        leap = 0;
    else if ((yr % 400) == 0)
        leap = 1;
    else if ((yr % 100)== 0)
        leap = 0;
    else 
        leap = 1;
    
    /*
     if ((yr % 4) != 0)        
        return 0;    
     if ((yr % 400) == 0)
        return 1;   
     if ((yr % 100) == 0)
        return 0
    return 1;
     */
    return leap;
    
}

void printAmerDate( int day, int month, int year)
{
    printf("%d/%d/%d",month, day, year);
    return;
}

void printEuroDate( int day, int month, int year)
{
    printf("%d,%d,%d",day, month, year);
    return;
}

void printISODate( int day, int month, int year)
{   
    printf("%d-%d-%d",year, month, day); 
    return;
}