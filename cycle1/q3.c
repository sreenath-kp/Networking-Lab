#include <stdio.h>
#include <unistd.h>
#include<sys/wait.h>
void main()
{
	char str[20];
	printf("Enter a string\n");
	scanf("%s", str);
	int pid = fork();
	if (pid == 0)
	{
		int i = 0;
		while (str[i] != '\0')
		{
			if (str[i] < 123 && str[i] > 96)
			{
				str[i] = str[i] - 32;
			}
			i++;
		}
		printf("%s\n", str);
	}
	wait(NULL);

}