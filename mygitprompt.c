//
// main is where all program execution starts
//

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

typedef struct gitstatus {
    char *branch_name;
    int added_count;
    int modified_count;
    int deleted_count;
    int untracked_count;
} GitStatus;


GitStatus* new_gitstatus(void) {
   GitStatus* gs = malloc(sizeof(GitStatus));
   if (gs == NULL) {
      return NULL; 
   }
   
   gs->branch_name = malloc(2049 * sizeof(char)); // 2048 characters plus null terminator
   if (gs->branch_name == NULL) {
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

int main(void) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    GitStatus *gs = NULL;

    fp = popen("git status --porcelain=v1 --branch -z", "r");
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
    while (getline(&line, &len, fp) != -1) {
        printf("%s", line);
    }

    pclose(fp);
    if (line)
        free(line);

    free_gitstatus(gs);
    return 0;
}
