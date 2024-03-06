#include <stdio.h>
#include <unistd.h>
void main()
{
	int pid = fork();
	if (pid < 0)
	{
		printf("fork failed\n");
	}
	else if (pid == 0)
	{
		printf("I am child, ");	
		printf("pid : %d\n", getpid());
	}
	else
	{
		
		printf("I am Parent, ");
		printf("pid : %d\n", getpid());
	}
}