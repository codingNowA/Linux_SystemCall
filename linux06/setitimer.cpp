#include<stdio.h>
#include<unistd.h>
#include<sys/time.h>
#include<signal.h>

void my_handler(int sig)
{
	printf("hello setitimer\n");
}

//每一秒执行一次my_handler
int main()
{
	itimerval timer;
	timer.it_interval.tv_sec=1;
	timer.it_interval.tv_usec=0;
	timer.it_value.tv_sec=1;
	timer.it_value.tv_usec=0;

	signal(SIGALRM,my_handler);
	setitimer(ITIMER_REAL,&timer,NULL);	

	while(1){}
	return 0;
}
