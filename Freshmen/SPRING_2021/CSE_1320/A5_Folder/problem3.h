#ifndef PROBLEM3_H_
#define PROBLEM3_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXDATE 8
#define MAXSIZE 12
#define MAXSIZEBUFFER 1280

typedef struct {
	char id[MAXSIZE];
	char date[MAXDATE];
	char *message;
} flight;

void remove_newline(char *);

#endif 