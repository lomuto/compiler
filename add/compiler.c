#include "postfix.h"
#include "parse.h"

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

	parse(BUFFER);
	
	fd = open("assembly.s", O_WRONLY | O_CREAT | O_EXCL, 0b111111111);
	if (fd == -1) {
		perror("OPEN ERROR");
		return 0;
	}
	// var dec
	char data_section[] = ".section .data\nN:.int V\nN:.int V\n";
	for (int i = 0,count=0; i < strlen(data_section); i++) {
		if (*(data_section + i) == 'N')
			*(data_section + i) = token.name[count];

		else if (*(data_section + i) == 'V')
			*(data_section + i) = token.val[count++];
	}


	char global_section[] = ".global main\n\nmain:\nmovl (V), %eax\nadd (V), %eax\nret";
	for (int i = 0, count = 0; i < strlen(global_section); i++) {
		if (*(global_section + i) == 'V')
			*(global_section + i) = token.name[count++];
	}
	
	strcat(data_section, global_section);
	
	if(write(fd, data_section, strlen(data_section)) == -1)
		perror("WRITE ERROR");
	close(fd);

	if (fork() == 0) {

		execlp("gcc", "gcc", "assembly.s", "-o", *(argv+2), NULL);

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