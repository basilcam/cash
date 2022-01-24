#include <string.h>
#include "command.h"
#include "builtin.h"
#include "consts.h"

void cmd_init(command *cmd,
              char buffer[BUFFER_SIZE],
              void (*parse_argv_argc)(char buffer[BUFFER_SIZE], char *argv[MAX_ARGS], size_t *argc),
              bool (*parse_bg)(char *argv[MAX_ARGS], size_t *argc),
              builtin (*parse_builtin)(char **argv)) {
    parse_argv_argc(buffer, cmd->argv, &cmd->argc);
    if (cmd->argc == 0) {
        return;
    }
    cmd->is_bg = parse_bg(cmd->argv, &cmd->argc);
    cmd->builtin = parse_builtin(cmd->argv);
}

bool cmd_is_bg_job(const command *cmd) {
    return cmd->is_bg;
}

builtin cmd_get_builtin(const command *cmd) {
    return cmd->builtin;
}

char * const *cmd_get_argv(const command *cmd) {
    return cmd->argv;
}

size_t cmd_get_argc(const command *cmd) {
    return cmd->argc;
}
