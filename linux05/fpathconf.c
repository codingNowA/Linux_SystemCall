#include <stdio.h>
#include <unistd.h>
#include <errno.h>

struct conf_name {
    int name;
    const char *desc;
};

int main(void) {
    struct conf_name list[] = {
        {_PC_LINK_MAX, "最大硬链接数 (_PC_LINK_MAX)"},
        {_PC_MAX_CANON, "终端规范模式下输入行的最大长度 (_PC_MAX_CANON)"},
        {_PC_MAX_INPUT, "终端输入缓冲区大小 (_PC_MAX_INPUT)"},
        {_PC_NAME_MAX, "文件名最大长度 (_PC_NAME_MAX)"},
        {_PC_PATH_MAX, "路径名最大长度 (_PC_PATH_MAX)"},
        {_PC_PIPE_BUF, "管道/FIFO 原子写入缓冲区大小 (_PC_PIPE_BUF)"},
        {_PC_CHOWN_RESTRICTED, "非root用户是否禁止chown (_PC_CHOWN_RESTRICTED)"},
        {_PC_NO_TRUNC, "超过最大长度的文件名是否被截断 (_PC_NO_TRUNC)"},
        {_PC_VDISABLE, "终端特殊字符禁用值 (_PC_VDISABLE)"},
   };

    int n = sizeof(list) / sizeof(list[0]);
    long val;
    int i;

    printf("查询文件描述符 STDOUT_FILENO 的 fpathconf 参数：\n\n");

    for (i = 0; i < n; i++) {
        errno = 0;
        val = fpathconf(STDOUT_FILENO, list[i].name);
        printf("%-50s: ", list[i].desc);

        if (val == -1) {
            if (errno == 0)
                printf("无上限（无限制）\n");
            else
                perror("");
        } else {
            printf("%ld\n", val);
        }
    }

    return 0;
}

