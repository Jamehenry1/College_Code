/*
 * 
 * Lab 1 Part 2 - Testing Multiplication and Division in C
 * 
 */

/* 
 * File:   main.c
 * Author: nghia
 *
 * Created on September 6, 2020, 5:46 PM
 * 
 * Name: Nghia Lam
 * UTA ID: 1001699317
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
int main(int argc, char** argv) {
    
    int age1 = 24;
    int age2;
    int age3 = 50,age4;
    age4 = 36;
    
    printf("Printing variable values: \n");
    printf("age1 = %d\nage2 = %d\n",age1,age2);
    printf("age3 =");
    printf("%d ",age3);
    printf("age4 = %d\n",age4);
    age2 = 9;
    printf("new value of age2 = %d\n",age2);
    
    printf("Product of age1 & age2 = %d\n",(age1 * age2) );
    printf("Sum of age1 & age2 = %d\n", (age1 + age2) );         
    printf("");      // prints a blank line
    printf("Giving age4 the value of age3 minus age1 so ");
    printf("%d - %d = ",age3,age1);
    age4 = age3 - age1;
    printf("%d\n",age4);

    printf("\nage1 = %d and age2 = %d\n",age1,age2);
    age4 = age1 / age2;     // Using integer variables:
    printf("\nUsing integer variables:        Quotient of %d & %d = %d\n",age1,age2,age4 ); 
    double age5 = age1 / age2 ;  // Using floating point variables:
    printf("Using int division assigned to floating point variables: Quotient of %d & %d = %f\n",age1,age2,age5);
    age5 = age1 / (double) age2 ;   // Using floating point with cast:
    printf("Using mixed division with cast assigned to floating point variables: Quotient of %d & (double)%d = %f\n\n",age1,age2,age5);

 
    return (EXIT_SUCCESS);
}

