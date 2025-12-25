#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

const int NUM=5;

void* thread_func(void *argc)
{
	int id=*(int*)argc;
	free(argc);
	printf("我是第%d个子线程\n",id);
	
	return NULL;
}

int main()
{
	pthread_t tid[NUM];	
	
	for(int i=0;i<NUM;i++)
	{
		int* id=(int*)malloc(sizeof(int));
		*id=i+1;
		pthread_create(&tid[i],NULL,thread_func,(void*)id);
	}

	for(int i=0;i<NUM;i++)
	{
		pthread_join(tid[i],NULL);
	}

	return 0;
}
