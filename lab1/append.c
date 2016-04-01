#include<fcntl.h>
#include<unistd.h>

int main (void) {
	int fd;
	char buf[] = "abcdefg";

	if ((fd = open ("out.out",O_RDWR | O_APPEND, 0)) == -1)
		printf("Error\n");
	
	long seek;
/*	if ((seek = lseek(fd, 0, SEEK_END)) == -1)
		printf("Error in lseek\n");*/
        // test O_APPEND
	if ((seek = lseek(fd, 0, SEEK_SET)) == -1 )
		printf("Error\n");
	if (write(fd, buf, 7) == -1)
		printf("Write error\n");
	exit(0);
}
	 
