#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>
#include<iostream>
using namespace std;
const int child_num=3;
int waitCHILD_num=0;

void child_handler(int sig)
{
	int status=0;
	while(wait(&status)!=-1)
	{
		waitCHILD_num++;
		printf("当前已经回收了%d个子进程...\n",waitCHILD_num);
	}
}

int main()
{
	sigset_t mask;
	sigemptyset(&mask);
	sigaddset(&mask,SIGCHLD);

	struct sigaction act;
	act.sa_handler=child_handler;
	sigaction(SIGCHLD,&act,NULL);

	//注册完成后再取消阻塞
	sigdelset(&mask,SIGCHLD);	

	for(int i=0;i<child_num;i++)
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
			printf("我是第%d个子进程（pid：%d)\n",i+1,getpid());
			sleep(0.5);
			printf("第%d个子进程工作结束，即将退出\n",i+1);
			exit(0);
		}

		else
		{
			printf("我是父进程...\n");
		}
	}

	while(waitCHILD_num!=child_num)
	{
		sleep(0.5);
	}
	printf("所有子进程已回收，父进程结束\n");
	return 0;
}
