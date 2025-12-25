#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdlib.h>

void exec_myapp()
{
	pid_t pid;
	pid=fork();
	if(pid<0)
	{
		printf("fork failed...\n");
		exit(1);
	}
	else if(pid==0)
	{
		printf("子进程即将执行./myapp...\n");
		execl("./myapp","myapp","hello","myapp!!!",NULL);
		printf("execl failed...\n");
		exit(1);
	}
	else{}
	return;
}

void exec_sysCommand()
{
	pid_t pid;
	pid=fork();
	if(pid<0)
	{
		printf("fork failed...\n");
		exit(1);
	}
	else if(pid==0)
	{
		printf("系统命令即将执行./myapp...\n");
		execlp("ls","ls","-l","-h",NULL);
		printf("execl failed...\n");
		exit(1);
	}
	else{}
}

int main()
{
	printf("父进程开始，父进程pid:%d\n",getpid());

	exec_myapp();
	sleep(1);
	exec_sysCommand();
	
	for(int i=0;i<2;i++)
	{
		int status;
		pid_t ended_pid=wait(&status);
		if(WIFEXITED(status))
		{
			printf("子进程(pid:%d)已退出，状态码%d\n",ended_pid,WIFEXITED(status));
		}
	}
	
	printf("所有子进程结束，父进程退出！\n");
	return 0;
}
