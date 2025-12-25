#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>

int main()
{
	pid_t pid;
	int fd[2];
	pipe(fd);

	pid=fork();

	if(pid<0)
	{
		printf("fork failed...\n");
		exit(1);
	}

	else if(pid==0)
	{
		close(fd[1]);
		dup2(fd[0],STDIN_FILENO);
		close(fd[0]);
		execlp("grep","grep","bash",NULL);
		exit(0);
	}

	else
	{
		close(fd[0]);
		dup2(fd[1],STDOUT_FILENO);
		close(fd[1]);
		execlp("ps","ps","aux",NULL);
	}

	int status;
	pid_t ended_pid=wait(&status);
	if(WIFEXITED(status))
	{
		printf("子进程(pid:%d)已退出,状态码:%d\n",ended_pid,WEXITSTATUS(status));
	}

	return 0;
}
