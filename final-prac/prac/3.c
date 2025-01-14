#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

int READ_END = 0;
int WRITE_END = 1;

void handler(int sig)
{
    if (sig == SIGUSR1)
    {
        // This is used for synchronization between parent and child
    }
}

int main()
{
    int p1[2]; // Pipe for reading and writing

    pipe(p1);

    int fd1 = open("foo", O_CREAT | O_RDWR, 0666); // set permissions
    int fd2 = dup(fd1);
    pid_t pid = fork(); // Creating process

    signal(SIGUSR1, handler); // Make sure that both the parent and the child have signal handler

    if (pid == 0)
    { // Child process
        char *msg = "Hi, Mom";
        write(fd2, msg, strlen(msg)); // Child writes to file
        kill(getppid(), SIGUSR1); // Signal the parent process
        pause();                  // Wait for the message from the parent

        close(p1[WRITE_END]); // close the writing for the pipe, because we are now just reading

        char msg2[64];
        if (read(p1[READ_END], msg2, sizeof(msg2)) > 0)
        { // Read message that the parent sent
            printf("My Mom said %s\n", msg2);
            close(p1[READ_END]);
        }

        return 0;
    }
    else
    { // Parent process
        pause(); // make sure we wait for the child process
        lseek(fd1, SEEK_SET, 0);
        char msg[64];
        read(fd1, msg, sizeof(msg));
        printf("My son said %s\n", msg);

        close(p1[READ_END]); // close because we are no longer reading and will now write

        char *msgBuf = "what do you want\0";
        write(p1[WRITE_END], msgBuf, strlen(msgBuf));
        kill(pid, SIGUSR1); // signal the child process

        close(p1[WRITE_END]);
    }

    return 0;
}