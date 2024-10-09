#include "gitstatus.h"

int main(void) {
    printf("hello test\n");

    char line1[] = "## main...origin/main [ahead 9, behind 14]";
    char line2[] = "## test...origin/test [ahead 5]";
    char line3[] = "## branch...origin/branch [behind 20]";
    char line4[] = "## branch2...origin/branch2";

    GitStatus *gs = new_gitstatus();
    parse_branch_name(line1, gs);
    parse_ahead_behind(line1, gs);
    printf("Branch: %s, Ahead: %d, Behind: %d\n", gs->branch_name, gs->ahead_count, gs->behind_count);
    gs->ahead_count=0;
    gs->behind_count=0;
    printf("Test 1 passed");
    parse_ahead_behind(line2, gs);
    printf("Branch: %s, Ahead: %d, Behind: %d\n", gs->branch_name, gs->ahead_count, gs->behind_count);
    gs->ahead_count=0;
    gs->behind_count=0;
    printf("Test 2 passed");
    parse_ahead_behind(line3, gs);
    printf("Branch: %s, Ahead: %d, Behind: %d\n", gs->branch_name, gs->ahead_count, gs->behind_count);
    gs->ahead_count=0;
    gs->behind_count=0;
    printf("Test 3 passed");
    parse_ahead_behind(line4, gs);
    printf("Branch: %s, Ahead: %d, Behind: %d\n", gs->branch_name, gs->ahead_count, gs->behind_count);
    printf("Test 4 passed\n");
    free_gitstatus(gs);
    return 0;
}
