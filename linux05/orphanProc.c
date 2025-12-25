#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<errno.h>

int main()
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
		printf("这是子进程（pid:%d）,当前父进程pid:%d,睡眠两秒等待父进程结束\n",getpid(),getppid());
		sleep(1);
		printf("已成为孤儿进程(pid:%d),当前父进程pid:%d!!!\n",getpid(),getppid());
	}

	else{
		printf("这是父进程，父进程即将退出...\n");
		printf("父进程已退出...\n");
		exit(0);
	}

	return 0;
}
