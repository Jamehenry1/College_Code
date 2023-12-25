#include "creature.h"

int main(int argc, char **argv){

	if(argc != 3){
		return 1;
	}

	FILE *fp = fopen(argv[1],"r");
	int zoneChoice = atoi(argv[2]);

	if(fp == NULL) {
		return 1;
	}

	creatures c;
	//c.name = calloc(0, sizeof(char));

	while(1){

		fread(&c, sizeof(c) - sizeof(char *),1,fp);

		if(feof(fp)){
			break;
		}

		int length = c.size - (sizeof(c) - sizeof(char *));
		c.name = malloc(length * sizeof(char));

		fread(c.name, sizeof(char), length,fp);

		if(zoneChoice == c.zone){

			printf("Name: %s\n",c.name);
			printf("CR: %d\n",c.cr);
			printf("HP: %d\n",c.hp);
			printf("AC: %d\n",c.ac);
			printf("Zone: %d\n",c.zone);
			
		}

	}

	free(c.name);
	

	return 0;
}