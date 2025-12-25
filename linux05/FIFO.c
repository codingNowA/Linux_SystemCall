#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>
#define FIFO_filepath "myfifo"

int main()
{
	for(int i=0;i<2;i++)
	{
		pid_t pid;
		pid=fork();

		if(pid<0) exit(1);//fork failed
		else if(pid==0)
		{	
			printf("这是第%d个子进程\n",i+1);
			if(i==0)
			{
				if(mkfifo(FIFO_filepath,0666)==-1)
				{
					perror("mkfifo");
					exit(1);
				}
				else{//第一个子进程负责写
					printf("FIFO file has been created!\n");
					int fd=open(FIFO_filepath,O_WRONLY,0666);
					char* msg="hello world";

					write(fd,msg,strlen(msg));
					printf("msg has been sent!\n");
					close(fd);	
					exit(0);
				}
			}

			else//第二个子进程负责读
			{
				int fd=open(FIFO_filepath,O_RDONLY,0666);
				char msg[20];
			
				int n=read(fd,msg,sizeof(msg)-1);
				close(fd);
				msg[n]='\0';
			
				printf("msg has been received!!msg:%s\n",msg);
				exit(0);
			} 
		}
		else
		{
			printf("这是父进程,当前创建的是第%d个子进程\n",i+1);
			if(i==0) sleep(1);//保证读进程在写进程之后创建
		}
	}

	while(wait(NULL)>0);
	return 0;
}
