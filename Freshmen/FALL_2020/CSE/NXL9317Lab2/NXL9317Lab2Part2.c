/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: nghia
 *
 * Created on October 4, 2020, 6:39 PM
 * 
 * Name: Nghia Huynh Lam
 * UTA ID: 1001699317
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * Lab 2 Part 2: Printing out my name and its ASCII
 */
int main(int argc, char** argv) {
    
    //2.a) CODE    
    char N = 'N';
    char g = 'g';
    char h = 'h';
    char i = 'i';
    char a = 'a';
    printf("%c %c %c %c %c", N,g,h,i,a);
    printf("%d %d %d %d %d", N,g,h,i,a);

    //2.b) CODE
    printf("\n\n%c     %c     %c     %c     %c", N,g,h,i,a);
    printf("\n%d   %d   %d   %d   %d\n", N,g,h,i,a);
    
    //2.c) CODE
    char name[] = "Nghia";
        for (int i=0; i< 5; i++)
    {
        int nameNum = name[i];
        printf("\n%c = %d\n",name[i],nameNum);
    }
    
    return (EXIT_SUCCESS);
}

