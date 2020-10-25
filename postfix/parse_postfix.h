#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#define LEX_LEN 100
#define MAX_LINE 10
#define HASH(x) x%5
#define TABLE_SIZE 5

int TABLE[TABLE_SIZE] = { 0, };

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

	temp = strtok(NULL, " =;\n");
	strcpy(return_STAT, temp);

	cnt = 0;
	for (int i = 0; i < TABLE_SIZE; i++) {
		*(TABLE + HASH(*(var + cnt) - 'a')) = *(var + cnt + 1)-'0';
		cnt += 2;
	}

	return;
}