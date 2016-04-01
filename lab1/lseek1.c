#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>

char buf1[] = "abcdrfghij";
char buf2[] = "ABCDEFGHIJ";
// this is the authority of different users
// user:110 group:100 other:100
#define FILE_MODE 0644

int main (void) {
	int fd;

	if ((fd = creat("file.hole", FILE_MODE)) < 0) {
		printf("creat error\n");
		exit(1);
	}
	
	if (write(fd, buf1, 10) != 10) {
		printf("buf1 write error\n");
		exit(1);
	}

	if (lseek(fd, 40, SEEK_SET) == -1) {
		printf("lseek error\n");
		exit(1);
	}

	if (write(fd, buf2, 10) != 10) {
		printf("buf2 write error\n");
		exit(1);
	}

	exit(0);
}

