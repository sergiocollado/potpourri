#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

int main(int argc, char *argv[])
{
	int fd;
	unsigned int i = 0;

	fd = open("/dev/msg", O_RDWR);
	if (fd < 0) {
		perror("fd failed");
		exit(2);
	}
	for (i = 0; i < 2UL*INT_MAX; i++);
	close(fd);
}
