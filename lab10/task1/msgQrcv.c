#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct my_msgbuf
{
	long mtype;
	char mtext[200];
};

int main(void)
{
	struct my_msgbuf buf;
	int msqid, n, n2;
	key_t key;

	if ((key = ftok("msgQsnd.c", 'B')) == -1)
	{
		perror("ftok error");
		exit(1);
	}

	if ((msqid = msgget(key, 0644)) == -1)
	{
		perror("msgget error");
		exit(1);
	}
	printf("Ready\n");
	for (;;)
	{

		if (msgrcv(msqid, (struct msgbuf *)&buf, sizeof(buf), 0, 0) == -1)
		{
			perror("msgrcv error");
			exit(1);
		}
		if (sscanf(buf.mtext, "%d%d", &n, &n2) == 2)
		{
			printf("Sum of %d, %d: %d\n", n, n2, n + n2);
		}
		else
		{
			printf("Message did not contain two integers\n");
		}
	}
	return 0;
}
