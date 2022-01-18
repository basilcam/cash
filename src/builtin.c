#include <stdlib.h>
#include "builtin.h"

void handle_exit();

// todo: this will need to be updated to take argv/argc
void handle_builtin(builtin builtin) {
    switch (builtin) {
        BUILTIN_EXIT:
            handle_exit();
            break;
        BUILTIN_NONE:
        default:
            // todo: throw a warning
            return;
    }
}

void handle_exit() {
    // todo: should optionally take arg n specifying exit code
    // todo: should use previous jobs exit code
    exit(EXIT_SUCCESS);
}
