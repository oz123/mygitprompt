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
   return gs;
}

void free_gitstatus(GitStatus* gs) {
  if (gs != NULL) {
     free(gs->branch_name); // Free the memory pointed to by branch_name
     free(gs->remote_name); // Free the memory pointed to by branch_name
     free(gs); // Then free the struct itself
  }
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
    }// else {
        //printf("Dot not found in the string\n");
    //}
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

char* extract_substring(char *line) {
    // Find the "..." in the input string
    const char *start = strstr(line, "...");
    if (start != NULL) {
        // Move pointer to the beginning of the substring after "..."
        start += 3;

        // Find the '/' in the input string after "..."
        const char *end = strchr(start, '/');

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
    gs->remote_name = extract_substring(line);
}
