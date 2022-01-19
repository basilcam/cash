#include <string.h>
#include "command.h"
#include "builtin.h"
#include "consts.h"

void cmd_init(command *cmd,
              char buffer[BUFFER_SIZE],
              void (*parse_argv_argc)(char buffer[BUFFER_SIZE], char *argv[MAX_ARGS], size_t *argc),
              bool (*parse_bg)(char *argv[MAX_ARGS], size_t argc),
              builtin (*parse_builtin)(char **argv)) {
    strncpy(cmd->buffer, buffer, BUFFER_SIZE);
    parse_argv_argc(cmd->buffer, cmd->argv, &cmd->argc);
    if (cmd->argc == 0) {
        return;
    }
    cmd->is_bg = parse_bg(cmd->argv, cmd->argc);
    cmd->builtin = parse_builtin(cmd->argv);
}

bool cmd_is_bg_job(command *cmd) {
    return cmd->is_bg;
}

bool cmd_is_fg_job(command *cmd) {
    bool is_bg = cmd->is_bg;
    bool is_fg = !is_bg;
    return is_fg;
}

builtin cmd_get_builtin(command *cmd) {
    return cmd->builtin;
}

char * const *cmd_get_argv(command *cmd) {
    return cmd->argv;
}

size_t cmd_get_argc(command *cmd) {
    return cmd->argc;
}
