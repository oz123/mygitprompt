#define _GNU_SOURCE
#include "gitstatus.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

GitStatus* new_gitstatus(void) {
   GitStatus *gs = malloc(sizeof(GitStatus));
   if (gs == NULL) {
      return NULL; 
   }

   gs->branch_name = NULL;
   gs->remote_name = NULL;
   gs->tag_name = NULL;
   gs->stash_count = 0;
   gs->staged_count = 0;
   gs->modified_count = 0;
   gs->deleted_count = 0;
   gs->untracked_count = 0;
   gs->ahead_count = 0;
   gs->behind_count = 0;
   return gs;
}

void free_gitstatus(GitStatus* gs) {
  if (gs != NULL) {
      if (gs->branch_name != NULL) {
         free(gs->branch_name); // Free the memory pointed to by branch_name
         gs->branch_name = NULL;
      }
      if (gs->remote_name) {
         free(gs->remote_name); // Free the memory pointed to by remote_name
         gs->remote_name = NULL;
      }
      if (gs->tag_name) {
          free(gs->tag_name);
          gs->tag_name = NULL;
      }
      free(gs); // Then free the struct itself
  }
}

int parse_tag_name(char *line, GitStatus *gs){
    FILE *fp;
    size_t len = 0;

    fp = popen("git describe --tags", "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        return 1;
    }

    if (getline(&line, &len, fp) != -1) {
       // Remove the trailing newline character
       line[strlen(line) - 1] = '\0';
       gs->tag_name = (char *)malloc(len);
       if (gs->tag_name == NULL) {
            printf("Memory allocation for tag_name failed\n");
            return 1;
       }
       strncpy(gs->tag_name, line, len-1);
    }
    return 0;
}

bool is_tag(char *line) {
    if (!strcmp(line, "## HEAD (no branch)\n")) {
        return true;
    }
    return false;
}

void parse_ahead_behind(char *line, GitStatus *gs) {
    char *p;
    int ahead = 0, behind = 0;

    // Find the first occurrence of [ahead in the string
    p = strstr(line, "[ahead ");
    if (p) {
        sscanf(p, "[ahead %d", &ahead);
        gs->ahead_count = ahead;
    }

    // Find the first occurrence of ", behind " in the string
    p = strstr(line, ", behind ");
    if (p) {
        sscanf(p, ", behind %d", &behind);
        gs->behind_count = behind;
    }
    // Find the first occurrence of [behind n] in the string
    p = strstr(line, "[behind ");
    if (p) {
        sscanf(p, "[behind %d", &behind);
        gs->behind_count = behind;
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
    }
}

int parse_stash_count(GitStatus *gs) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;

    gs->stash_count = 0;

    fp = popen("git rev-list --walk-reflogs --count refs/stash  2>&1", "r");

    if (fp == NULL) {
        printf("Failed to run command\n" );
        return 1;
    }

    if (getline(&line, &len, fp) != -1) {
        gs->stash_count = atoi(line);
    } else {
	gs->stash_count = 0;
        //printf("Failed to parse stash count\n" );
        return 1;
    }
    return 0;
}

/*
   Match a string between two markers
   given a string like 'main...origin/main'
   calling extract_between("main...origin/main", "...", "/")
   will return 'origin'
*/
char* extract_between(char *line, const char *start_marker, const char *end_marker) {
    // Find the "..." in the input string
    const char *start = strstr(line, start_marker);
    if (start != NULL) {
        // Move pointer to the beginning of the substring after start_marker
        start += 3;

        // Find the end_marker in the input string after start_marker
        const char *end = strstr(start, end_marker);

        // Calculate the length of the substring
        if (end != NULL) {
            size_t length = end - start;
            char *output = (char *)malloc((length + 1) * sizeof(char)); // +1 for null terminator
            if (output == NULL) {
                printf("Memory allocation failed\n");
                return NULL;
            }

            strncpy(output, start, length);
            output[length] = '\0'; // Null-terminate the output string

            return output;
        }
    }
    return NULL;
}

void parse_remote_name(char *line, GitStatus *gs) {
    char *value = extract_between(line, "...", "/");
    if (value != NULL) {
        gs->remote_name = extract_between(line, "...", "/");
    }
}
