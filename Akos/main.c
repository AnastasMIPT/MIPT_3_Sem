#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int main () {
    char* line = NULL;
    size_t len = 0;
    int read = 0;
    char buf[PATH_MAX];
    while ((read = getline (&line, &len, stdin)) != -1)
    {
        line[read - 1] = '\0';
        if (line[0] == '\0' || line[0] == '\n') continue;
        struct stat stats = {};
        lstat (line, &stats);
        if (S_ISREG (stats.st_mode)) {
            buf[0] = '\0';
            strcat (buf, "link_to_");
            strcat (buf, line);
            symlink (line, buf);
        } else if (S_ISLNK (stats.st_mode)) {
            char real_path[PATH_MAX];
            realpath (line, real_path);
            printf ("%s\n", real_path);
        }
            
    }
    if (line) free (line);
}