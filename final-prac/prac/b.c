#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf
{
    long mtype;
    char mtext[200];
};

int main(void)
{
    struct msgbuf buf;
    int msqid, n1, n2;
    key_t key;

    key = ftok("a.c", 'B');

    msqid = msgget(key, 0644);

    for(;;)
    {
        msgrcv(msqid, (struct msgbuf *)&buf, sizeof(buf), 0, 0 );
        if(sscanf(buf.mtext, "%d%d", &n1, &n2) == 2)    
        {
            msgsnd(msqid, (struct msgbuf *)&buf, sizeof(buf), 0);
            printf("valid\n");
        }
        else
        {
            printf("no two integers\n");
        }
    }
}