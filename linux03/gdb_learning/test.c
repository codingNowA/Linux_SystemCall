#include <stdio.h>
#include <time.h>

int main(void)
{
    time_t raw;
    struct tm *info;

    time(&raw);
    info = localtime(&raw);

    printf("Hello, C!\n");
    printf("Current local time: %s", asctime(info));

    return 0;
}
