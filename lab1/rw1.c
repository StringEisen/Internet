#include<fcntl.h>
#include<unistd.h>

int main (void) {
	char quit = ".";
	char buf[10];
	#define FILE_MODE 0644
	int fd;

	if ((fd = creat("out.out", FILE_MODE)) < 0)
		printf("creat error\n");
	if (open ("out.out", O_RDWR, 0) == -1)
		printf("Error in opening\n");
	while(buf[0] != quit) {
		read(0, buf, 1);
		write(fd, buf, 1);
		write(1, buf, 1);
	}
	close(fd);
}

