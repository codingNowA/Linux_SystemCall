#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<string.h>
#include<inttypes.h>

int main()
{
	int fd;
	//fd=open("test03.txt",O_RDWR|O_APPEND,0664); O_APPEND会导致后面设置的偏移量无效
	fd=open("test03.txt",O_RDWR,0664);

	if(fd==-1)
	{
		const char* buf_t="file open failed...\n";
		write(1,buf_t,strlen(buf_t));
	}
	
	//先将文件指针置于开头
	lseek(fd,0,SEEK_SET);	

	//获取文件长度
	off_t len=lseek(fd,0,SEEK_END);
	if(len==(off_t)-1)
	{
		perror("lseek:");
	}
	
	char buf_len[30];
	sprintf(buf_len,"test03.txt的长度为%"PRIdMAX"\n",(intmax_t)len);
	write(1,buf_len,strlen(buf_len));

	//拓展文件
	off_t extend_len=lseek(fd,20,SEEK_END);
	write(fd,"newEnd",6);

	return 0;
}
