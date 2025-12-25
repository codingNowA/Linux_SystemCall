#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<time.h>

int cnt=0;
bool keep_cnt=true;

void alarm_handler(int sig)
{
	keep_cnt=false;
}

//程序一秒能数多少个数
int main()
{
	signal(SIGALRM,alarm_handler);
	printf("start！\n");
	alarm(1);
	
	while(keep_cnt){cnt++;}
	printf("程序一秒数了%d个数\n",cnt);	
	
	return 0;
}
