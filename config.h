

// Config file for gitprompt

#ifndef CONFIG_H
#define CONFIG_H
#include <stdbool.h>
#include "gitstatus.h"
#include "colors.h"

#define GITICON "±"
#define GITCLEAN "✓"
#define GITDIRTY "✗"
#define UNSTAGED "U" 
#define UNTRACKED "?"
#define STAGED "S"

/*
void show_prompt(GitStatus *gs){
    printf("Branch Name: %s\n", gs->branch_name);
    printf("Untracked: %d\n", gs->untracked_count);
    printf("Modified: %d\n", gs->modified_count);
    printf("Staged: %d\n", gs->staged_count);
    printf("Deleted: %d\n", gs->deleted_count);
}
*/

// TODO: Handle tags
void show_prompt(GitStatus *gs) {
    bool dirty = false;
    printf("[");
    printf(FG_GREEN GITICON FG_WHITE);
    if (gs->tag_name == NULL) {
        printf("|%s → %s", gs->branch_name, gs->remote_name);
        if (gs->ahead_count > 0) {
            printf(" ↑%d", gs->ahead_count);
        }
        if (gs->behind_count > 0) {
            printf("↓%d", gs->behind_count);
        }
        if (gs->staged_count > 0) {
            printf(" "STAGED ":%d", gs->staged_count);
            dirty = true;
        }
        if (gs->modified_count > 0) {
             printf(" "UNSTAGED ":%d", gs->modified_count);
             dirty = true;
        }
        if (gs->untracked_count > 0) {
            printf(" "UNTRACKED ":%d", gs->untracked_count);
            dirty = true;
        }
        if (dirty) {
           printf(" "FG_RED BOLD GITDIRTY NORMAL FG_WHITE"|");
        } else {
           printf(" "GITCLEAN"|");
        }
    } else {
        printf("tag:%s", gs->tag_name);
        printf(" "GITCLEAN"|");
    }
    printf(RESET_COLOR);
    printf("]");
}
#endif // CONFIG_H
