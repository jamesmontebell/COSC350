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
    int msqid;
    key_t key;

    key = ftok("a.c", 'B');

    msqid = msgget(key, 0644 | IPC_CREAT);
    buf.mtype = 1;
    while(gets(buf.mtext), !feof(stdin))
    {
        msgsnd(msqid, (struct msgbuf *)&buf, sizeof(buf), 0);
    }
    msgctl(msqid, IPC_RMID, NULL);
}