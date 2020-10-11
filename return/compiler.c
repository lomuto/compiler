#include "postfix.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#define BLKSIZE 128
#define EXE_FILE_NAME "x.out"
int get_return_val(const char*);

int main(int argc, char* argv[]) {
	char EXP[MAX_EXP];
	

	char BUFFER[BLKSIZE];
	int fd = open(*(argv+1), O_RDONLY);
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

	char return_val = get_return_val(BUFFER);

	char pre_assembly_code[] = ".global main\n\
\n\
main:\n\
\tmovl $";

	*(pre_assembly_code + strlen(pre_assembly_code)) = return_val;
	*(pre_assembly_code + strlen(pre_assembly_code) + 1) = NULL;

	char suf_assembly_code[] = ", %eax\n\tret";

	strcat(pre_assembly_code, suf_assembly_code);
	
	if(write(fd, pre_assembly_code, strlen(pre_assembly_code)) == -1)
		perror("WRITE ERROR");
	close(fd);

	if (fork() == 0) {

		execlp("gcc", "gcc", "assembly.s", "-o", *(argv+2), NULL);

		perror("execlp failed");
	}
	int stat_loc;
	wait(stat_loc);

	if(fork() == 0)
		execlp("run", "run", NULL);
	wait(stat_loc);
}

int get_return_val(const char* BUFFER) {
	for (; *BUFFER != NULL; BUFFER++)
		if (isdigit(*BUFFER))
			return *BUFFER;
}