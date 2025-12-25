#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("dup_test.txt", O_CREAT | O_WRONLY | O_TRUNC, 0664);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    int newfd = dup(fd);
    if (newfd < 0) {
        perror("dup");
        return 1;
    }

    write(fd, "hello ", 6);
    write(newfd, "world\n", 6);

    close(fd);
    close(newfd);

    return 0;
}

