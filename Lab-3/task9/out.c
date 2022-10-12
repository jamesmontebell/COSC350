#include <stdio.h>

#include <stdlib.h>

#include <fcntl.h>

#include <unistd.h>

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)



void error_sys(char *str)

{

    printf("%s", str);

    exit(1);

}



int main(int argc, char* argv[])

{

    if(argc < 3)

    {

        error_sys("Error1");

    }



    int in, out, new;

    char buf;





    if((in = open(argv[1], O_RDONLY)) < 0)

    {

        error_sys("Error2");

    }

    if((out = open(argv[2], O_CREAT | O_EXCL | O_WRONLY, FILE_MODE)) < 0)

    {

        error_sys("Error3");

    }

    if((new = dup2(out, 1)) < 0)

    {

        error_sys("error");

    }

    if(in != -1)

    {

        while((read(in, &buf, 1)) > 0)

        {

            if(buf == 10)

            { 

                printf("\n");

            }

            if(buf == " ")

            {

                printf("%d ", (int)buf);

            }

            printf("%d ", buf);

        }

    }

    else

    {

        error_sys("error");

    }

    close(in);

    close(out);

    return 0;

}


