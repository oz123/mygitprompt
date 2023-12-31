//
// main is where all program execution starts
//

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct gitstatus {
    char *branch_name;
    int added_count;
    int modified_count;
    int deleted_count;
    int untracked_count;
} GitStatus;


GitStatus* new_gitstatus(void) {
   GitStatus *gs = malloc(sizeof(GitStatus));
   if (gs == NULL) {
      return NULL; 
   }
   
   return gs;
}


void free_gitstatus(GitStatus* gs) {
  if (gs != NULL) {
     free(gs->branch_name); // Free the memory pointed to by branch_name
     free(gs); // Then free the struct itself
  }
}

void parse_branch_name(char *line, GitStatus *gs) {
    char *p;
    char *dotp;
    int len;
    // Skip the first two characters (## and a space)
    p = line + 3;

    // Find the first 3 dots in the string
    dotp = strstr(p, "...");

    // If a dot was found
    if (dotp) {
        // Calculate the length of the substring before the first dot
        len = dotp - p;

        // Allocate memory for the branch string
        gs->branch_name = (char *)malloc(len + 1);
        if (gs->branch_name == NULL) {
            printf("Memory allocation failed\n");
            return;
        }

        // Copy the substring to the branch string
        strncpy(gs->branch_name, p, len);

        // Ensure the branch string is null-terminated
        gs->branch_name[len] = '\0';
    } else {
        printf("Dot not found in the string\n");
    }
}

int main(void) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    GitStatus *gs = NULL;

    fp = popen("git status --porcelain=v1 --branch", "r");
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

    while (getline(&line, &len, fp) != -1) {
        printf("%s", line);
    }

    pclose(fp);
    if (line)
        free(line);

    printf("Branch Name: %s\n", gs->branch_name);
    free_gitstatus(gs);
    return 0;
}
