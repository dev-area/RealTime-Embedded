#include<windows.h>
#include "publisher.h"

void f1()
{
	static int count=0;
	printf("f1:%d\n",++count);
}
void f2()
{
	static int count=0;
	printf("f2:%d\n",++count);
}
void f3()
{
	static int count=0;
	printf("f3:%d\n",++count);
}

int main(int argc, char *argv[], char *envp[])
{
	Subscriber s1,s2,s3;
	s1.update = f1;
	s2.update = f2;
	s3.update = f3;

	InitAppTimer();

	//RegisterOnInterval(&s1,500);
	RegisterOnInterval(&s2,200);
	RegisterOnInterval(&s3,100);

	StartAppTimer();

	return 0;
}
