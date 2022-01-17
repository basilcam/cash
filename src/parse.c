#include "parse.h"
#include <stdlib.h>
#include <string.h>

int parseline(char *buf, char **argv) {
    char *delim;
    int argc;
    int bg;

    // replace trailing \n with space
    buf[strlen(buf)-1] = ' '; 

    // ignore leading spaces
    while (*buf && (*buf == ' ')) { 
        buf++;
    }

    // build argv
    argc = 0;
    while ((delim = strchr(buf, ' '))) {
        argv[argc++] = buf;
        *delim = '\0'; 
        buf = delim + 1;

        // ignore trailing spaces
        while (*buf && (*buf == ' ')) {
            buf++;
        }
    }
    argv[argc] = NULL;

    if (argc == 0) {
        return 1;
    }

    // determine if should run in background
    // if so, remove & from argv
    if ((bg = (*argv[argc-1] == '&')) != 0 ) {
        argv[--argc] = NULL;
    }

    return bg;
}

int is_builtin_command(char **argv) {
    if (!strcmp(argv[0], "quit")) {
        exit(EXIT_SUCCESS);
    }
    if (!strcmp(argv[0], "&")) {
        return 1;
    }
    return 0;
}