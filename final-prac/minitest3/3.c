#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char *first = malloc(sizeof(argv[1]));
    int n = atoi(argv[1]);
    int i =0;

    while (n != 0)
    {
        first[i] = rand()%26+'a';
        n--;
        i++;
    }

    printf("%s\n", first);
    write(1, "more\n", 4);
    char ch;
    read(0, &ch, 1);

    int m = atoi(&ch);
    first = realloc(first, sizeof(i+m));
    while(m != 0)
    {
        first[i] = rand()%26+'a';
        m--;
        i++;
    }


    printf("%s", first);

    exit(0);
}