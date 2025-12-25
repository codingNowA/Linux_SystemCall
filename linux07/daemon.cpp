#include "my_header.h"
#include<cstring>
using namespace std;

//写时间的文件
#define LOG_FILE "/tmp/time.log"

void alarm_handler(int sig)
{
	time_t now;
	time(&now);
	char* time_str=ctime(&now);

	int fd=open(LOG_FILE,O_WRONLY|O_CREAT|O_APPEND,0644);
	if(fd!=-1)
	{	
		write(fd,time_str,strlen(time_str));
		close(fd);
	}
}

void daemonize()
{
	//第一步：调用fork
	pid_t pid;
	pid=fork();
	if(pid>0) exit(0);
	else if(pid<0) exit(1);

	//第二步：调用setsid（）
	setsid();

	//第三步：改变工作目录
	chdir("/");

	//第四步：重设文件掩码
	umask(0000);

	//第五步：关闭标准文件描述符
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

int main()
{
	//创建守护进程
	daemonize();	

	struct sigaction sa;
	struct itimerval timer;

	sa.sa_handler=alarm_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags=0;
	sigaction(SIGALRM,&sa,NULL);
	
	//设置定时器，每两秒触发一次
	timer.it_value.tv_sec=2;
	timer.it_value.tv_usec=0;
	timer.it_interval.tv_sec=2;
	timer.it_interval.tv_usec=0;
	setitimer(ITIMER_REAL,&timer,NULL);
	
	//执行核心工作
	while(1)
	{
		pause();
	}

	return 0;
}
