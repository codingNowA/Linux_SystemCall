#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>

#define CHILD_NUM 5 
int main()
{
	pid_t pid;
	
	for(int i=0;i<CHILD_NUM;i++)
	{
		pid=fork();
		if(pid<0)
		{
			printf("子进程fork失败...\n");
			exit(0);
		}
		else if(pid==0)
		{
			printf("我是子进程，成功被创建，pid=%d!\n",getpid());
			exit(0);
		}
		else
		{
			printf("我是父进程，我的pid是%d,当前创建了第%d个子进程，子进程pid是%d!!!\n",getpid(),i+1,pid);
		}
	}
	
	for(int i=0;i<CHILD_NUM;i++)
	{
		int status;
		pid_t ended_pid=wait(&status);
		if(WIFEXITED(status))
		{
			printf("子进程 %d 退出，状态码: %d\n", 
                   ended_pid, WEXITSTATUS(status));
		}
	}

	printf("所有子进程结束，父进程退出\n");	
	return 0;
}
