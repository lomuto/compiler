#include "postfix.h"
#include "parse.h"
#define BLKSIZE 100

void hasing(char* return_STAT);

int main(int argc, char* argv[]) {
	char EXP[MAX_EXP];


	char BUFFER[BLKSIZE];
	int fd = open(*(argv + 1), O_RDONLY);
	int read_bytes = read(fd, BUFFER, BLKSIZE);

	if (read_bytes == -1) {
		perror("Failed to open file");
		return 0;
	}
	close(fd);

	fd = open("assembly.s", O_WRONLY | O_CREAT | O_EXCL, 0b111111111);
	if (fd == -1) {
		perror("OPEN ERROR");
		return 0;
	}

	char return_STAT[30];
	parse(BUFFER, return_STAT);

	to_POSTFIX(return_STAT, strlen(return_STAT));

	hasing(return_STAT);

	// assembly code generator

	close(fd);

	FILE* fp = fopen("assembly.s", "w");		// write �� append �ϱ� ���� fopen ���
	
	fprintf(fp, ".global main\n\nmain:\n");

	clear_STACK();
	for (int i = 0; i < strlen(return_STAT); i++) {
		if (!isdigit(*(return_STAT + i))) {		// �о���� return exp�� �ܾ �������� ��
			switch (*(return_STAT + i)) {
			case '+':
				fprintf(fp, "pop %%rax\n");
				fprintf(fp, "pop %%rbx\n");
				fprintf(fp, "addq %%rbx, %%rax\n");
				fprintf(fp, "push %%rax\n");
					break;
			case '-':
				fprintf(fp, "pop %%rbx\n");				// 31- ==> 3-1
				fprintf(fp, "pop %%rax\n");				// pop -> 1, pop -> 3
				fprintf(fp, "subq %%rbx, %%rax\n");		// subq src,dest ==> dest = dest-src
				fprintf(fp, "push %%rax\n");
				break;
			case '*':
				fprintf(fp, "pop %%rax\n");
				fprintf(fp, "pop %%rbx\n");
				fprintf(fp, "imulq %%rbx, %%rax\n");
				fprintf(fp, "push %%rax\n");
				break;
			}
		}
		else
			fprintf(fp, "push $%d\n", *(return_STAT+i)-'0');
	}

	fprintf(fp, "pop %%rax\nret\n");

	fclose(fp);

	if (fork() == 0) {

		execlp("gcc", "gcc", "assembly.s", "-o", *(argv + 2), NULL);

		perror("execlp failed");
	}
	int stat_loc;
	wait(stat_loc);

	if (fork() == 0) {	

		execlp("rm", "rm", "assembly.s", NULL);

		perror("execlp failed");
	}
	wait(stat_loc);
}

void hasing(char* return_STAT) {
	for (int i = 0; *(return_STAT + i) != '\0'; i++) {
		if (isalpha(*(return_STAT + i))) {
			*(return_STAT+i) = *(TABLE + *(return_STAT + i)-'a')+'0';
		}
	}
}