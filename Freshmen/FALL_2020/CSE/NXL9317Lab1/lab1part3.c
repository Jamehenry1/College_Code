/*
 * 
 * Lab 1 Part 3 - Doing fractional math with C
 * 
 */

/* 
 * File:   main.c
 * Author: nghia
 *
 * Created on September 6, 2020, 7:03 PM
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
    
    int a = 1;
    int b = 4;
    int c = 3;
    int d = 10;

    printf("Original fractions are ");
    printf("%d/%d and %d/%d\n",a,b,c,d);

    int num1st = a * d;
    int num2nd = b * c;
    int denom = b * d;
    printf("The terms in the numerator are ");
    printf("%d and %d and the denominator is %d\n",num1st, num2nd, denom);

    double fractionSum = (num1st + num2nd)/ (double) denom;
    printf("The equation for the sum of two fractions is ");
    printf("(%d + %d)/%d = %d/%d\n",num1st, num2nd, denom, (num1st + num2nd), denom);

    printf("The sum of the two fractions is %f", fractionSum);   //Version 3 CORRECTION


    return (EXIT_SUCCESS);
}

