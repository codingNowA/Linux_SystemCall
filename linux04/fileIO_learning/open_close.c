#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
int main()
{
	int fd;
	char* buf="hello open&&close func!\n";
	fd = open("test00.txt",O_RDWR|O_CREAT,0664);
	if(fd==-1)
	{
		write(1,"file open failed...\n",20);
		return 0;
	}
	write(fd,buf,strlen(buf));
	close(fd);
	write(1,"write file succseefully!\n",25);
	return 0;
}
