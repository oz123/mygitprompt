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

#ifndef GITSTATUS_H   // Inclusion guard
#define GITSTATUS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
//
// on why we use 
// typedef struct <Tag>{
    // fields
// } NameOfStruct
// https://stackoverflow.com/a/20532390/492620

typedef struct gitstatus {
    char *branch_name;
    char *remote_name;
    char *tag_name;
    int stash_count;
    int staged_count;
    int modified_count;
    int deleted_count;
    int untracked_count;
    int ahead_count;
    int behind_count;
} GitStatus;

GitStatus* new_gitstatus(void);
char *extract_between(char *line, const char *start_marker, const char *end_marker);
void free_gitstatus(GitStatus* gs);
bool is_tag(char *line);
void parse_branch_name(char *line, GitStatus *gs);
void parse_remote_name(char *line, GitStatus *gs);
void parse_ahead_behind(char *line, GitStatus *gs);
int parse_tag_name(char *line, GitStatus *gs);
int parse_stash_count(GitStatus *gs);

#endif /* GITSTATUS_H */
