/* 
 This file is part of mygitprompt.

 mygitprompt is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License, version 3 or later
 as published by the Free Software Foundation;

 mygitprompt is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with mygitprompot; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

 Copyright (C) 2024 Oz N Tiram <oz.tiram@gmail.com>
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gitstatus.h"
#include "config.h"

//#define VERSION "v0.0.2-4-g14da1ce-dirty"

int main(int argc, char *argv[]){
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    GitStatus *gs = NULL;
    char *cmd = NULL;

    if (argc > 1) {
        cmd = argv[1];
        if (!strcmp(cmd, "--help")){
            printf("Usage: mygitprompt [--help|version]\n\n");
            printf("Show current git status in a form useful for usage with your shell prompt.\n\n");
            printf("If no arguments are given, mygitprompt will show the current git status.\n\n");
            printf("Options:\n");
            printf("  --help    Show this help message\n");
            printf("  --version Show the version of mygitprompt\n\n");
            printf("mygitprompt is a free software distributed under the tersm of GPLv3\n");
            return 0;
        }
        if (!strcmp(cmd, "--version")){
            printf("mygitprompt version %s\n", VERSION);
            printf("mygitprompt is a free software distributed under the tersm of GPLv3\n");
            return 0;
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
    // first line has always the branch name and ahead behing
    if (getline(&line, &len, fp) != -1) {
        if (is_tag(line)) {
            parse_tag_name(line, gs);
        } else {
            parse_branch_name(line, gs);
            parse_remote_name(line, gs);
            parse_ahead_behind(line, gs);
        }
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
            gs->staged_count+=1;
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
