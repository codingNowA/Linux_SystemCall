#include<stdio.h>
#include<unistd.h>

int main(int argc,char* argv[])
{
	printf("=== 这是我的自定义程序 ===\n");
    printf("程序名称: %s\n", argv[0]);
    printf("进程ID: %d\n", getpid());
    printf("父进程ID: %d\n", getppid());
    
    // 显示参数
    printf("参数个数: %d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("参数[%d]: %s\n", i, argv[i]);
    }
    
    printf("程序执行完毕！\n");
	return 0;
}
