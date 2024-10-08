//
// main is where all program execution starts
//

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gitstatus.h"
#include "config.h"

int main(int argc, char *argv[]){
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    GitStatus *gs = NULL;
    char *cmd = NULL;

    if (argc > 1) {
        cmd = argv[1];
	if (!strcmp(cmd, "version")){
            printf("mygitprompt version %s\n", VERSION);
        } else {
            printf("Unknown command ...\n");
            return 1;
	}
    }
    fp = popen("git status --porcelain=v1 --branch 2>&1", "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        return 1;
    }

    gs = new_gitstatus();
    if (gs == NULL) {
       // handle error, e.g., print an error message and exit
       printf("Failed to allocate memory for GitStatus.\n");
       exit(EXIT_FAILURE);
    }

    // first line is always the branch name
    if (getline(&line, &len, fp) != -1) {
        parse_branch_name(line, gs);
    }

    char filestatus[3];
    // https://git-scm.com/docs/git-status
    while (getline(&line, &len, fp) != -1) {
        snprintf(filestatus, sizeof(filestatus), "%s", line);
        if (strcmp(filestatus, "??") == 0) {
            gs->untracked_count+=1;
        } else if (strcmp(filestatus, " M") == 0) {
            gs->modified_count+=1;
        } else if (strcmp(filestatus, " D") == 0) {
            gs->modified_count+=1;
        } else if (strcmp(filestatus, "MM") == 0) {
            gs->staged_count+=1;
            gs->modified_count+=1;
        } else if (strcmp(filestatus, "D ") == 0) {
            gs->modified_count+=1;
        } else if (strcmp(filestatus, "RD") == 0) {
            gs->modified_count+=1;
            gs->staged_count+=1;
        } else if (strcmp(filestatus, "M ") == 0) {
            gs->modified_count+=1;
        } else if (strcmp(filestatus, "R ") == 0) {
            gs->modified_count+=1;
        } else if (strcmp(filestatus, "A ") == 0) {
            gs->staged_count+=1;
        } else if (strcmp(filestatus, "AM") == 0) {
            gs->staged_count+=1;
            gs->modified_count+=1;
        } else if (strcmp(filestatus, "??") == 0) {
            gs->untracked_count+=1;
        }

    }

    int status = pclose(fp);
    if (line)
        free(line);
    if (status == 0){
        parse_stash_count(gs);
        show_prompt(gs);
    }
    free_gitstatus(gs);
    return 0;
}
