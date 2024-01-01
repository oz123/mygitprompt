#ifndef GITSTATUS_H   // Inclusion guard
#define GITSTATUS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// on why we use 
// typedef struct <Tag>{
    // fields
// } NameOfStruct
// https://stackoverflow.com/a/20532390/492620

typedef struct gitstatus {
    char *branch_name;
    int staged_count;
    int modified_count;
    int deleted_count;
    int untracked_count;
    int ahead_count;
    int behind_count;
} GitStatus;

GitStatus* new_gitstatus(void);
void free_gitstatus(GitStatus* gs);
void parse_branch_name(char *line, GitStatus *gs);
void parse_ahead_behind(char *line, GitStatus *gs);

#endif /* GITSTATUS_H */