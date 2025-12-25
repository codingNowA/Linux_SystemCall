#include<unistd.h>
#include<time.h>
#include<signal.h>
#include<iostream>
using namespace std;

int main()
{
	sigset_t mask;

	sigaddset(&mask,SIGINT);
	sigprocmask(SIG_BLOCK,&mask,NULL);	
	printf("SIGINT has been obstructed!!!,CTRL+C is useless whithin three seconds\n");
	
	sleep(3);
	sigprocmask(SIG_UNBLOCK,&mask,NULL);
	printf("CTRL+C is available now...\n");
	while(1){};
	return 0;
}
