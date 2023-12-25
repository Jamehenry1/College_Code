#include "problem3.h"

int main(int argc, char **argv) {
	if(argc != 2) {
		return 1;
	}

	FILE *fp = fopen(argv[1], "r");

	if(fp == NULL) {
		return 1;
	}

	flight f;

	char buffer[MAXSIZEBUFFER];
	char *temp;


	while(1){

		//fread(buffer,1280,1,fp);
		fgets(buffer, 1280,fp);
		remove_newline(buffer);
		//printf("%s\n", buffer);
		temp = strtok(buffer,",");
		strcpy(f.id,temp);

		temp = strtok(NULL,",");
		f.message = malloc(strlen(temp)*sizeof(char));
		strcpy(f.message,temp);

		temp = strtok(NULL,",");
		strcpy(f.date,temp);

		//printf("%s\n", f.id);
		
		//f.message = strtok(NULL, ",");
		//f.date = strtok(NULL,",");
		//printf("%ld,%ld,%ld\n", strlen(f.date),strlen(f.id),strlen(f.message));
		printf("On %s %s Chirped, %s...\n", f.date,f.id,f.message);
		//printf("%ld\n", strlen(temp));
		//printf("%s\n", f.id);

		if(feof(fp)){
			break;
		}
	}

	free(f.message);


	return 0;

}

void remove_newline(char *str) {
    int l = strlen(str);
    if (str[l - 1] == '\n') {
        str[l - 1] = 0;
    }
}