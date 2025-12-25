#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>

int count=0;
pthread_mutex_t mutex;

void* pthread_count(void* argc)
{
	for(int i=0;i<5000;i++)
	{	
		pthread_mutex_lock(&mutex);
		int num=count;
		num++;
		count=num;
		printf("count=%d\n",count);
		pthread_mutex_unlock(&mutex);
	}

	pthread_exit(NULL);
}

//创建两个线程去数数（使用全局变量，加锁保护）
int main()
{
	pthread_mutex_init(&mutex,NULL);
	pthread_t tid[2];
	pthread_create(&tid[0],NULL,pthread_count,NULL);
	pthread_detach(tid[0]);
	pthread_create(&tid[1],NULL,pthread_count,NULL);
	pthread_detach(tid[1]);

	pthread_exit(NULL);
	return 0;
}
