#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* thread_func(void* arg)
{
    while (1)
    {
        printf("子线程运行中...\n");
        sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t tid;

    // 1. 创建线程（默认 joinable）
    pthread_create(&tid, NULL, thread_func, NULL);

    // 2. 创建后设置为分离状态
    pthread_detach(tid);

    // 3. 主线程继续干自己的事
    sleep(5);

    printf("主线程退出\n");
    return 0;
}

