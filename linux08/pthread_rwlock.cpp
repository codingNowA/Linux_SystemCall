#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// 共享资源 - 一个简单的数字
int shared_number = 0;

// 读写锁
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

// 写线程函数 - 3个线程会不定时增加这个数字
void* writer(void* arg) {
    int id = *(int*)arg;  // 线程编号
    
    for(int i = 0; i < 3; i++) {  // 每个写线程增加3次
        // 随机等待1-3秒，模拟不定时写入
        sleep(rand() % 3 + 1);
        
        // 获取写锁（独占锁）
        pthread_rwlock_wrlock(&rwlock);
        
        // 修改共享资源
        shared_number++;
        printf("写线程 %d: 把数字改成 %d\n", id, shared_number);
        
        // 释放写锁
        pthread_rwlock_unlock(&rwlock);
    }
    return NULL;
}

// 读线程函数 - 5个线程会不定时读取这个数字
void* reader(void* arg) {
    int id = *(int*)arg;  // 线程编号
    
    for(int i = 0; i < 2; i++) {  // 每个读线程读取2次
        // 随机等待1-2秒，模拟不定时读取
        sleep(rand() % 2 + 1);
        
        // 获取读锁（共享锁）
        pthread_rwlock_rdlock(&rwlock);
        
        // 读取共享资源
        printf("读线程 %d: 看到数字是 %d\n", id, shared_number);
        
        // 释放读锁
        pthread_rwlock_unlock(&rwlock);
    }
    return NULL;
}

int main() {
    pthread_t writers[3];  // 3个写线程
    pthread_t readers[5];  // 5个读线程
    int writer_ids[3] = {1, 2, 3};
    int reader_ids[5] = {1, 2, 3, 4, 5};
    
    printf("开始！初始数字 = %d\n\n", shared_number);
    
    // 创建3个写线程
    for(int i = 0; i < 3; i++) {
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }
    
    // 创建5个读线程
    for(int i = 0; i < 5; i++) {
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }
    
    // 等待所有写线程完成
    for(int i = 0; i < 3; i++) {
        pthread_join(writers[i], NULL);
    }
    
    // 等待所有读线程完成
    for(int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
    }
    
    printf("\n结束！最终数字 = %d\n", shared_number);
    printf("预期数字 = %d (0 + 3个线程 × 3次 = 9)\n", 9);
    
    return 0;
}
