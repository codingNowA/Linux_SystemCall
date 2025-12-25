#include<stdio.h>
#include <unistd.h>   // 声明 read()、write()
#include <string.h>   // 声明 strlen()
int main()
{
	char buf[100];
	write(1,"enter your buf\n",15);
	read(0, buf, sizeof(buf));   // 从标准输入（键盘）读
	write(1, buf, strlen(buf));  // 写到标准输出（屏幕）
	return 0;
}
