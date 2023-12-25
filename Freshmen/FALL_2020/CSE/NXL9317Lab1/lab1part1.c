/*
 * 
 * Lab 1 Part 1 - Testing different types of outputs with math addition and subtraction
 * 
 */

/* 
 * File:   main.c
 * Author: nghia
 *
 * Created on September 1, 2020, 11:06 PM
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
    
    printf("Testing string output and arithmetic with negative numbers\n");
    printf("%d\n",23);
    printf("%d\n",-84);
    printf("%d - %d\n",23,-84);
    printf("%d\n",23- -84);
    
    printf("Testing more output and arithmetic\n");
    printf("7 + 55 = \n");
    printf("%d\n", 7 + 55);
    printf("7.0 + 55.0 = \n");
    printf("%f\n", 7.0 + 55.0);        
    printf("7 + 55 = ");
    printf("%d", 7 + 55); 
    printf("%f\n", 7.0 + 55.0); 
    printf("");
    
    printf("Mathematically 7 + 55 = %d and %f\n", (7+55), (7.0+55.0));

    printf("%d\n",7 + 55);     //  and

    printf("%d",7 + 55);  

    return (EXIT_SUCCESS);
}

