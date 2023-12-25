#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSTRING 1280



typedef struct
{
	int hp;
	int ac;
	int speed;
	char *name;
	char *type;
} Creature;

void remove_newline(char *);
void fileRead(FILE *fp,Creature c,Creature *creatureStorage);
int compareName(const void *elem1, const void *elem2);
int compareType(const void *elem1, const void *elem2);
int compareHP(const void *elem1, const void *elem2);
int compareAC(const void *elem1, const void *elem2);
int compareSpeed(const void *elem1, const void *elem2);

void release_tree(Creature *root);
void printStructArr(Creature *creatureStorage,int amountMonster);