#include <stdlib.h>
#include "builtin.h"

void handle_exit();

// todo: this will need to be updated to take argv/argc
void handle_builtin(builtin abuiltin) {
    switch (abuiltin) {
        case BUILTIN_EXIT:
            handle_exit();
            break;
        case BUILTIN_NONE:
            break;
    }
}

void handle_exit() {
    // todo: should optionally take arg n specifying exit code
    // todo: should use previous jobs exit code
    exit(EXIT_SUCCESS);
}
