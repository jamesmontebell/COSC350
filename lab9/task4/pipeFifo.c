#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#define READ_END 0
#define WRITE_END 1

int main()
{
    const char some_data[] = "123";
	int fd, ffd, data_processed;
	
    char *buffer = malloc(sizeof(some_data));

    fd = open("/tmp/task4_fifo", O_RDWR);

    data_processed = write(fd, some_data, strlen(some_data));
    printf("Wrote %d bytes\n", data_processed);

    data_processed = read(fd, buffer, strlen(some_data));
    printf("Read %d bytes: %s\n", data_processed, buffer);
    close(fd);

    exit(EXIT_FAILURE);
}