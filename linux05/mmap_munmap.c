#include<sys/mman.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>

int main()
{
	int fd=open("test_mman.txt",O_RDWR|O_CREAT,0666);
	if(fd==-1)
	{
		perror("open");
		exit(1);
	}	
	const char* buf="hello,mmap and munmap funcs!!!\n";
	write(fd,buf,strlen(buf));

	int file_size=lseek(fd,0,SEEK_END);	
	void* mapped=mmap(NULL,file_size,PROT_WRITE|PROT_READ,MAP_SHARED,fd,0);
	if(mapped==MAP_FAILED)
	{
		perror("mmap");
		exit(1);
	}	

	printf("mmap_file content:%s\n",(char*)mapped);
	printf("请输入您的文本以改变内存映射文件...\n");
	char user_buf[100];
	fgets(user_buf,sizeof(user_buf),stdin);	
	user_buf[strlen(user_buf)]='\0';

	strcpy((char*)mapped,user_buf);
	printf("Now mmap_file content:%s\n",(char *)mapped);
	

//	file_size=lseek(fd,0,SEEK_END);
	close(fd);
	if(munmap(mapped,file_size)==-1)
	{
		perror("munmap");
		exit(1);
	}
	return 0;
}
