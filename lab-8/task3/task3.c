#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	int n, fd[2];
	char in[256];
	pid_t pid;

	if (pipe(fd) < 0)
	{
		perror("pipe error\n");
		exit(1);
	}

	pid = fork();

	if(pid < 0)
	{
		perror("fork error\n");
		exit(1);
	}

	if(pid == 0)
	{
		close(fd[1]);
		int int1, int2;

		while((n = read(fd[0], in, 256))>0)
		{
			if(sscanf(in, "%d%d", &int1, &int2) == 2)
			{
				sprintf(in, "Sum: %d\n", int1+int2);

				n = strlen(in);

				if(write(0, in, n) != n)
				{
					printf("write error");
					exit(1);
				}
			}
			else
			{
				if(write(0, "invalid args\n", 13) != 13)
				{
					printf("write error");
					exit(1);
				}
			}
		}
	}

	else
	{
		close(fd[0]);
		int i;
		printf("input 2 integers: \n");

		while((fgets(in, 256, stdin) != NULL))
		{
			n = strlen(in);
	
			if(write(fd[1], in, n) != n)
			{
				printf("Write error");
				exit(1);
			}		
		}
	}
	exit(0);
}