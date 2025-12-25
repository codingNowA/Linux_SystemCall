#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

// 各种类型的全局变量
int global_int = 100;
char global_str[50] = "Hello World";
double global_double = 3.14159;
int* global_ptr;

void print_globals(const char* process_name) {
    printf("[%s] 全局变量状态:\n", process_name);
    printf("  global_int = %d, 地址: %p\n", global_int, &global_int);
    printf("  global_str = \"%s\", 地址: %p\n", global_str, global_str);
    printf("  global_double = %f, 地址: %p\n", global_double, &global_double);
    printf("  *global_ptr = %d, 堆地址: %p\n", *global_ptr, global_ptr);
    printf("  global_ptr指针地址: %p\n", &global_ptr);
    printf("\n");
}

int main() {
    // 初始化堆内存
    global_ptr = (int*)malloc(sizeof(int));
    *global_ptr = 999;
    
    printf("=== 详细全局变量共享测试 ===\n");
    printf("初始状态:\n");
    print_globals("初始");
    
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("fork失败");
        exit(1);
    } else if (pid == 0) {
        // 子进程
        printf("🎯 子进程开始工作 (PID: %d)\n", getpid());
        
        printf("1. 子进程读取初始值:\n");
        print_globals("子进程-读取");
        
        printf("2. 子进程修改全局变量:\n");
        global_int = 200;
        strcpy(global_str, "Child Modified");
        global_double = 2.71828;
        *global_ptr = 1111;
        
        print_globals("子进程-修改后");
        
        printf("3. 子进程睡眠2秒，等待父进程读取...\n");
        sleep(2);
        
        printf("4. 子进程最终读取:\n");
        print_globals("子进程-最终");
        
        printf("🎯 子进程退出\n");
        exit(0);
    } else {
        // 父进程
        printf("👨 父进程继续执行 (PID: %d)\n", getpid());
        
        printf("1. 子进程创建后，父进程立即读取:\n");
        print_globals("父进程-初始");
        
        printf("2. 等待1秒让子进程先修改...\n");
        sleep(1);
        
        printf("3. 父进程读取（子进程已修改）:\n");
        print_globals("父进程-子修改后");
        
        printf("4. 父进程也修改全局变量:\n");
        global_int = 300;
        strcpy(global_str, "Parent Modified");
        global_double = 1.41421;
        *global_ptr = 2222;
        
        print_globals("父进程-修改后");
        
        // 等待子进程结束
        int status;
        wait(&status);
        
        printf("5. 子进程退出后，父进程最终读取:\n");
        print_globals("父进程-最终");
        
        printf("👨 父进程退出\n");
    }
    
    // 清理
    free(global_ptr);
    return 0;
}
