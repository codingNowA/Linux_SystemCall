#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>

int main()
{
	int fd=open("if_exist.txt",O_RDWR,0664);
	if(fd==-1)
	{
		perror("open:");
	}

	close(fd);
	strerror(errno);
	return 0;
}
