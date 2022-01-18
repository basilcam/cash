#include <string.h>
#include <assert.h>
#include "parse.h"

void parse_argv_argc(char *buffer, char **argv, size_t *argc) {
    char *delim;

    // replace trailing \n with space
    // todo: safety!
    buffer[strlen(buffer)-1] = ' ';

    // ignore leading spaces
    while (*buffer && (*buffer == ' ')) {
        buffer++;
    }

    // build argv
    size_t arg_count = 0;
    while ((delim = strchr(buffer, ' '))) {
        argv[arg_count++] = buffer;
        *delim = '\0';
        buffer = delim + 1;

        // ignore trailing spaces
        while (*buffer && (*buffer == ' ')) {
            buffer++;
        }
    }
    argv[arg_count] = NULL;
    *argc = arg_count;
}

bool parse_bg(char **argv, size_t argc) {
    // todo: add debug-only assertions in libcam
    assert(argc > 0);
    bool is_bg = *argv[argc-1] == '&';

    if (is_bg) {
        argv[--argc] = NULL;
    }

    return is_bg;
}

builtin parse_builtin(char **argv) {
    if (!strcmp(argv[0], "exit")) {
        return BUILTIN_EXIT;
    }
    return BUILTIN_NONE;
}
