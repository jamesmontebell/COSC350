#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

char* mygetenv(char * var)
{
    int len = strlen(var);  
    char path[4000];

    for(int i = 0; environ[i] != NULL; i++)
    {
        if((strncmp(var, environ[i], len) == 0) && (environ[i][len] == '='))
        {
            strncpy(path, &environ[i][len+1], 4000); // len + 1 so '=' doesn't print
            return (path);
        }
    }
    return NULL;
}

int main()
{
    printf("%s\n", mygetenv("HOME"));
    printf("%s\n", mygetenv("PWD"));
    printf("%s\n", mygetenv("TERM"));
    return 0;
}