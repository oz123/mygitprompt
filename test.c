#include <assert.h>
#include <string.h>
#include "gitstatus.h"

int main(void) {
    printf("hello test\n");

    char *branches[] = {
        "main", "test", "branch", "branch2"
    };

    char *origins[] = {
        "origin", "origin", "mine", "upstream"
    };

    int aheads[] = {9, 5, 0, 0};
    int behinds[] = {14, 0, 20, 0};

    char *git_status_lines[] = {
        "## main...origin/main [ahead 9, behind 14]",
        "## test...origin/test [ahead 5]",
        "## branch...mine/branch [behind 20]",
        "## branch2...upstream/branch2",
    };

    for (int i=0; i<4; i++) {
        GitStatus *gs = new_gitstatus();

        parse_branch_name(git_status_lines[i], gs);
        parse_remote_name(git_status_lines[i], gs);
        parse_ahead_behind(git_status_lines[i], gs);

        assert(!strcmp(branches[i], gs->branch_name));
        assert(!strcmp(origins[i], gs->remote_name));
        free_gitstatus(gs);
        printf("Test %d passed\n", i+1);
    }

    return 0;
}
