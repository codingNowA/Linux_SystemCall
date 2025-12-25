#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/mman.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/wait.h>


int main()
{
	char user_buf[100];
	printf("请输入您想传输的内容\n");
	fgets(user_buf,sizeof(user_buf),stdin);
	
	int fd=open("test_commu_mmap.txt",O_RDWR|O_CREAT,0666);
	const char* init_data="-------init data(ignored)-------\n";
	write(fd,init_data,strlen(init_data));
	int file_size=lseek(fd,0,SEEK_END);	
	
	void* mmap_addr=mmap(NULL,file_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);

	pid_t pid;
	pid=fork();	
	
	if(pid<0)
	{
		perror("fork");
		exit(1);
	}
	else if(pid==0)
	{
		close(fd);
		printf("我是子进程,pid:%d\n,等待父进程数据传输到mmap_file\n",getpid());
		sleep(2);
		char receive_buf[500];
		strcpy(receive_buf,(char*)mmap_addr);
		printf("子进程已接收到信息:%s\n",receive_buf);
		exit(0);
	
		if(munmap(mmap_addr,file_size+strlen(user_buf)+1))
		{
			perror("munmap");
			exit(1);
		}
	}
	else
	{
		printf("我是父进程，pid:%d,正在传输数据到mmap_file\n",getpid());	
		strcat((char*)mmap_addr+file_size,"\n");
		strcpy((char*)mmap_addr+file_size+1,user_buf);
	
		close(fd);
		if(munmap(mmap_addr,file_size+strlen(user_buf)+1))
		{
			perror("munmap");
			exit(1);
		}

	
	}
	
	wait(NULL);
	return 0;
}
