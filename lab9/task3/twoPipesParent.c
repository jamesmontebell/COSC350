#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define READ_END 0
#define WRITE_END 1

int main()
{
    int data_processed;
    int file_pipes[2];
    int file_pipes2[2];
    const char some_data[] = "Hi there, kiddo";
    char buffer[BUFSIZ + 1];
    pid_t fork_result;
    memset(buffer, '\0', sizeof(buffer));
    if (pipe(file_pipes) == 0)
    {
        fork_result = fork();
        if (fork_result == (pid_t)-1)
        {
            fprintf(stderr, "Fork failure");
            exit(EXIT_FAILURE);
        }
        if (fork_result == 0)
        {
            char f_p0[BUFSIZ+1], f_p1[BUFSIZ+1], f_p20[BUFSIZ+1], f_p21[BUFSIZ+1];	
		
            memset(f_p0, '\0', sizeof(f_p0));	
            memset(f_p1, '\0', sizeof(f_p1));	
            memset(f_p20, '\0', sizeof(f_p20));	
            memset(f_p21, '\0', sizeof(f_p21));

            sprintf(f_p0, "% d", file_pipes[READ_END]);
            sprintf(f_p1, "% d", file_pipes[WRITE_END]);
            sprintf(f_p20, "% d", file_pipes2[READ_END]);
            sprintf(f_p21, "% d", file_pipes2[WRITE_END]);
  
            (void)execl("twoPipesChild", "twoPipesChild", f_p0, f_p1, f_p20, f_p21, (char *)0);
            exit(EXIT_FAILURE);
        }
        else
        {
            close(file_pipes[READ_END]);
            close(file_pipes2[WRITE_END]);
            data_processed = write(file_pipes[1], some_data, strlen(some_data));
            printf("% d - wrote % d bytes\n", getpid(), data_processed);
        }
    }
    exit(EXIT_SUCCESS);
}