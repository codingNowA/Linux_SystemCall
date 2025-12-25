#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int fd;
    int flags;

    // 打开文件（只写），若不存在则创建
    fd = open("fcntl_test.txt", O_WRONLY | O_CREAT, 0664);
    if (fd < 0)
    {
        perror("open");
        return 1;
    }

    // 1️⃣ 获取当前文件状态标志
    flags = fcntl(fd, F_GETFL);
    if (flags < 0)
    {
        perror("fcntl get");
        close(fd);
        return 1;
    }

    printf("原始标志: 0x%x\n", flags);

    // 2️⃣ 增加 O_APPEND 属性（末尾追加）
    flags |= O_APPEND;

    if (fcntl(fd, F_SETFL, flags) < 0)
    {
        perror("fcntl set");
        close(fd);
        return 1;
    }

    printf("已设置 O_APPEND 属性。\n");

    // 3️⃣ 写入内容（始终追加到文件末尾）
    const char *text = "hello fcntl append test\n";
    write(fd, text, strlen(text));

    close(fd);
    return 0;
}

