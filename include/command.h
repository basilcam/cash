#ifndef CAMSHELL_COMMAND_H
#define CAMSHELL_COMMAND_H

#include <stdbool.h>
#include "builtin.h"
#include "consts.h"

// do not access struct elements outside command.c
// they're only here to allow declarations
typedef struct {
    char buffer[BUFFER_SIZE];
    char *argv[MAX_ARGS];
    size_t argc;
    bool is_bg;
    builtin builtin;
} command;

void cmd_init(command *cmd,
              char buffer[BUFFER_SIZE],
              void (*parse_argv_argc)(char buffer[BUFFER_SIZE], char *argv[MAX_ARGS], size_t *argc),
              bool (*parse_bg)(char *argv[MAX_ARGS], size_t argc),
              builtin (*parse_builtin)(char **argv));

bool cmd_is_bg_job(command *cmd);

bool cmd_is_fg_job(command *cmd);

builtin cmd_get_builtin(command *cmd);

char * const *cmd_get_argv(command *cmd);

size_t cmd_get_argc(command *cmd);

#endif // CAMSHELL_COMMAND_H

