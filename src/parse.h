#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define LEX_LEN 100
#define MAX_LINE 10

int* TABLE;

int HASH(int size, char var){
	return (var-'a')%size;
}

void parse(char* EXP,char* return_STAT) {
	char var[20];

	char* temp = strtok(EXP, " =;\n");
	*var = *temp;
	int cnt = 1;

	while ((temp = strtok(NULL, " =;\n")) != NULL) {
		if (!strcmp(temp, "return"))
			break;
		*(var + cnt++) = *temp;
	}
	*(var + cnt) = '\0';

	int size = cnt/2;
	TABLE = calloc(size,sizeof(int));



	temp = strtok(NULL, " =;\n");
	strcpy(return_STAT, temp);

	cnt = 0;
	for (int i = 0; i < size; i++) {
		*(TABLE + HASH(size,*(var + cnt))) = *(var + cnt + 1)-'0';
		cnt += 2;
	}

	return;
}