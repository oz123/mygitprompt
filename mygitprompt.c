//
// main is where all program execution starts
//
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    size_t read;

    fp = popen("git status", "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        return 1;
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("%s", line);
    }

    pclose(fp);
    if (line)
        free(line);

    return 0;
}
