#include <assert.h>
#include <string.h>
#include "gitstatus.h"

int main(void) {
    printf("hello test\n");

    char line1[] = "## main...origin/main [ahead 9, behind 14]";
    char line2[] = "## test...origin/test [ahead 5]";
    char line3[] = "## branch...mine/branch [behind 20]";
    char line4[] = "## branch2...upstream/branch2";

    GitStatus *gs = new_gitstatus();

    parse_branch_name(line1, gs);
    parse_remote_name(line1, gs);
    parse_ahead_behind(line1, gs);

    assert(!strcmp("main", gs->branch_name));
    assert(!strcmp("origin", gs->remote_name));
    assert(gs->ahead_count == 9);
    assert(gs->behind_count == 14);
    free_gitstatus(gs);
    printf("Test 1 passed\n");

    gs = new_gitstatus();
    parse_branch_name(line2, gs);
    parse_remote_name(line2, gs);
    parse_ahead_behind(line2, gs);

    assert(!strcmp("test", gs->branch_name));
    assert(!strcmp("origin", gs->remote_name));
    assert(gs->ahead_count == 5);
    assert(gs->behind_count == 0);

    free_gitstatus(gs);
    printf("Test 2 passed\n");

    gs = new_gitstatus();
    parse_branch_name(line3, gs);
    parse_remote_name(line3, gs);
    parse_ahead_behind(line3, gs);

    assert(!strcmp("branch", gs->branch_name));
    assert(!strcmp("mine", gs->remote_name));
    assert(gs->ahead_count == 0);
    assert(gs->behind_count == 20);
    free_gitstatus(gs);
    printf("Test 3 passed\n");

    gs = new_gitstatus();
    parse_branch_name(line4, gs);
    parse_remote_name(line4, gs);
    parse_ahead_behind(line4, gs);

    assert(!strcmp("branch2", gs->branch_name));
    assert(!strcmp("upstream", gs->remote_name));
    assert(gs->ahead_count == 0);
    assert(gs->behind_count == 0);

    free_gitstatus(gs);
    printf("Test 4 passed\n");
    return 0;
}
