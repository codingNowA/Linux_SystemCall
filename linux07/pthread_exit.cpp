#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

struct argc
{
public:
	int a;
	int b;
}input;

void* pthread_func(void* argc)
{
	struct argc* p=(struct argc*) argc;
	int a=p->a;
	int b=p->b;
	int* res=(int*)malloc(sizeof(int));
	*res=a+b;
	pthread_exit((void*)res);
	return NULL;
}

int main()
{
	int a,b;
	printf("请输入a，b的值\n");
	scanf("%d%d",&a,&b);
	input.a=a,input.b=b;
	pthread_t tid;	
	pthread_create(&tid,NULL,pthread_func,(void*)&input);	
	
	void* ret;
	pthread_join(tid,&ret);
	printf("子线程的执行结果是%d+%d=%d\n",a,b,*(int*)ret);
	free(ret);
	return 0;
}
