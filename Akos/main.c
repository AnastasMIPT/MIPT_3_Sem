#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    char buf[BUFSIZ];
    char path[BUFSIZ];
    char protocol[BUFSIZ];

    scanf("%s", buf);
    scanf("%s", buf);
    scanf("%s", protocol);

    char* lexeme_p = strtok(buf, "?");
    strcpy(path, lexeme_p + 1);
    lexeme_p = strtok(NULL, "");

    if (access(path, F_OK) == -1) {
        printf("%s 404 ERROR\n\n", protocol);
        return 0;
    } else if (access(path, X_OK) == -1) {
        printf("%s 403 ERROR\n\n", protocol);
        return 0;
    } else {
        printf("%s 200 OK\n", protocol);
        fflush(stdout);
    }

    if (lexeme_p != NULL) {
        setenv("QUERY_STRING", lexeme_p, 1);
    } else {
        setenv("QUERY_STRING", "", 1);
    }

    while (fgets(buf, BUFSIZ, stdin) != NULL) {
        if (strstr(buf, "Host") != NULL) {
            strtok(buf, " \n\t");
            lexeme_p = strtok(NULL, " \n\t");
            setenv("HTTP_HOST", lexeme_p, 1);
        }
    }

    setenv("REQUEST_METHOD", "GET", 1);
    setenv("SCRIPT_NAME", path, 1);

    execl(path, path, NULL);
    return -1;
}
