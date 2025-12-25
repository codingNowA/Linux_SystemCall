#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
int main()
{
	int fd;
	fd=open("test01.txt",O_RDWR|O_APPEND,0664);
	if(fd==-1)
	{
		const char* buf_openFailed="file open failed...\n";
		write(1,buf_openFailed,strlen(buf_openFailed));
	}

	char user_input[100]="\0";
	const char* prompt="please enter your content,enter \":wq\" to finish!\n";
	write(1,prompt,strlen(prompt));
	while(strcmp(user_input,":wq\n\0")!=0)//这里要注意循环逻辑导致退出字符变化
	{
		int n=read(0,user_input,sizeof(user_input)-1);//不会自己+\0
		if(n>0) user_input[n]='\0';
		if(strcmp(user_input,":wq\n\0")!=0) write(fd,user_input,sizeof(user_input)-1);
	}

	close(fd);
	const char* buf_closeSuccess="file close successfully!\n";
	write(1,buf_closeSuccess,strlen(buf_closeSuccess));
	return 0;
}
