#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct gitstatus {
    char *branch_name;
    int added_count;
    int modified_count;
    int deleted_count;
    int untracked_count;
    int ahead_count;
    int behind_count;
};

/*
typedef struct gitstatus GitStatus;


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
int main(void) {
    GitStatus *gs = new_gitstatus();
    gs->added_count = 10;
    gs->modified_count = 5;
    gs->deleted_count = 2;
    gs->untracked_count = 3;
    gs->ahead_count = 4;
    gs->behind_count = 1;

    printf("Added Count: %d\n", gs->added_count);
    printf("Modified Count: %d\n", gs->modified_count);
    printf("Deleted Count: %d\n", gs->deleted_count);
    printf("Untracked Count: %d\n", gs->untracked_count);
    printf("Ahead Count: %d\n", gs->ahead_count);
    printf("Behind Count: %d\n", gs->behind_count);

    free_gitstatus(gs);

    return 0;
}
*/

struct gitstatus* new_gitstatus(void) {
    struct gitstatus *gs = malloc(sizeof(struct gitstatus));
    if (gs == NULL) {
        return NULL; 
    }
    return gs;
}

void free_gitstatus(struct gitstatus* gs) {
    if (gs != NULL) {
        free(gs->branch_name); // Free the memory pointed to by branch_name
        free(gs); // Then free the struct itself
    }
}

int main(void) {
    struct gitstatus *gs = new_gitstatus();
    gs->added_count = 10;
    gs->modified_count = 5;
    gs->deleted_count = 2;
    gs->untracked_count = 3;
    gs->ahead_count = 4;
    gs->behind_count = 1;

    printf("Added Count: %d\n", gs->added_count);
    printf("Modified Count: %d\n", gs->modified_count);
    printf("Deleted Count: %d\n", gs->deleted_count);
    printf("Untracked Count: %d\n", gs->untracked_count);
    printf("Ahead Count: %d\n", gs->ahead_count);
    printf("Behind Count: %d\n", gs->behind_count);

    free_gitstatus(gs);

    return 0;
}
