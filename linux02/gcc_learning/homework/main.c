#include<stdio.h>
#include"head.h"
int main()
{
	int a,b;
	printf("请输入a和b的值\n");
	scanf("%d%d",&a,&b);
	printf("a+b=%d,a-b=%d,a*b=%d,a/b=%f\n",add(a,b),sub(a,b),mul(a,b),dive(a,b));
	return 0;
}
