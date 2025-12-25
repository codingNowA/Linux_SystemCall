#include<iostream>
#include<unistd.h>
#include<signal.h>
using namespace std;

void my_handler(int sig)
{
	printf("成功进入捕捉处理SIGQUIT的函数\n");
}

int main()
{
	struct sigaction act;
	act.sa_handler=my_handler;
	sigset_t mask;
	sigemptyset(&mask);
	sigaddset(&mask,SIGINT);
	sigprocmask(SIG_BLOCK,&mask,NULL);//程序永久阻塞SIGINT
//	act.sa_mask=(mask&~SIGINT)|SIGQUIT;//信号处理期间也要屏蔽SIGQUIT
	//mask和SIGINT类型不同不能这样写，只能是理解上是这样
	sigemptyset(&mask);
	sigaddset(&mask,SIGQUIT);
	act.sa_mask=mask;//信号处理期间也要屏蔽SIGQUIT

	//处理SIGQUIT,ctrl+\; 
	sigaction(SIGQUIT,&act,NULL);
	printf("SIGINT已被阻塞，SIGQUIT将会被捕捉处理,要结束进程请强制杀死，本进程的pid为%d \n",getpid());
	while(1){}

	return 0;
}
