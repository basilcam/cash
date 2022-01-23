#include <stdlib.h>
#include "builtin.h"
#include "jobs.h"

static void handle_exit() {
    // todo: should optionally take arg n specifying exit code
    // todo: should use previous jobs exit code
    exit(EXIT_SUCCESS);
}

static void handle_jobs() {
    jobs_print();
}

// todo: this will need to be updated to take argv/argc
void builtin_handle(builtin abuiltin) {
    switch (abuiltin) {
        case BUILTIN_EXIT:
            handle_exit();
            break;
        case BUILTIN_JOBS:
            // todo
            handle_jobs();
            break;
        case BUILTIN_FG:
            // todo
            break;
        case BUILTIN_BG:
            // todo
            break;
        case BUILTIN_CD:
            // todo
            break;
        case BUILTIN_NONE:
        default:
            break;
    }
}

