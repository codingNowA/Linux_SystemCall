#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* thread_func(void* arg)
{
    for (int i = 0; i < 5; i++) {
        printf("分离线程运行中... %d\n", i);
        sleep(1);
    }
    printf("分离线程退出\n");
    return NULL;
}
int main()
{
    pthread_t tid;
    pthread_attr_t attr;

    /* 1. 初始化线程属性 */
	pthread_attr_init(&attr);
    /* 2. 设置线程为分离状态 */
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
    /* 3. 使用属性创建线程 */
	pthread_create(&tid,&attr,thread_func,NULL);
    /* 4. 销毁线程属性对象 */
	pthread_attr_destroy(&attr);
    /* 5. 主线程继续执行 */
    printf("主线程继续运行\n");
    sleep(3);

    printf("主线程退出\n");
    return 0;
}
