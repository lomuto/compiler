#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#define BLKSIZE 40
#define LEX_LEN 100
#define MAX_LINE 10
struct _token {
	char name[10];
	int val[10];
}token;

int read_line(char* BUFFER, char line[][LEX_LEN]) {
	int count = 0;
	char* temp;

	for (temp = strtok(BUFFER, "\n");temp != NULL ; count++) {	// temp를 거쳐서 strcpy해야함
		strcpy(*(line + count), temp);
		temp = strtok(NULL, "\n");
	}
	return --count;
}


char* parse(char* BUFFER) {
	char line[MAX_LINE][LEX_LEN];

	int lines = read_line(BUFFER, line);

	token.name[0] = **line;
	token.name[1] = **(line + 1);
	token.val[0] = *(*line + 4);
	token.val[1] = *(*(line + 1) + 4);
}