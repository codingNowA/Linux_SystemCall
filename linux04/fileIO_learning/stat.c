#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("用法: %s <文件名>\n", argv[0]);
        return 1;
    }

    struct stat st;
    if (stat(argv[1], &st) == -1) {
        perror("stat");
        return 1;
    }

    printf("文件: %s\n", argv[1]);
    printf("文件大小: %lld 字节\n", (long long)st.st_size);
    printf("硬链接数: %lu\n", (unsigned long)st.st_nlink);
    printf("所有者 UID: %u\n", st.st_uid);
    printf("所属组 GID: %u\n", st.st_gid);
    printf("文件模式(八进制): %o\n", st.st_mode & 07777);

    // 判断文件类型
    if (S_ISREG(st.st_mode))       printf("类型: 普通文件\n");
    else if (S_ISDIR(st.st_mode))  printf("类型: 目录\n");
    else if (S_ISLNK(st.st_mode))  printf("类型: 符号链接\n");
    else if (S_ISCHR(st.st_mode))  printf("类型: 字符设备\n");
    else if (S_ISBLK(st.st_mode))  printf("类型: 块设备\n");
    else if (S_ISFIFO(st.st_mode)) printf("类型: FIFO 管道\n");
    else if (S_ISSOCK(st.st_mode)) printf("类型: 套接字\n");
    else                           printf("类型: 未知\n");

    return 0;
}

