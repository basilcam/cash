#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <cam/sys/process.h>
#include <sys/wait.h>
#include "evaluate.h"
#include "consts.h"
#include "parse.h"
#include "command.h"

extern char **environ;

void evaluate(char buffer[BUFFER_SIZE]) {
    command cmd;
    cmd_init(&cmd,
             buffer,
             parse_argv_argc,
             parse_bg,
             parse_builtin);

    if (cmd_get_argc(&cmd) == 0) {
        return;
    }

    if (cmd_get_builtin(&cmd) == BUILTIN_NONE) {
        // execute command in child process
        pid_t pid;
        if ((pid = cam_fork()) == 0) {
            char * const *argv = cmd_get_argv(&cmd);
            if (execve(argv[0], argv, environ) < 0) {
                printf("%s: Command not found.\n", argv[0]);
                exit(EXIT_SUCCESS);
            }
        }

        // wait for command if not background
        if (cmd_is_fg_job(&cmd)) {
            int status;
            if (waitpid(pid, &status, 0) < 0) {
                cam_handle_unix_error("waitfg: waitpid error");
            }
        } else {
            printf("%d, %s", pid, buffer);
        }

    } else {
        handle_builtin(cmd_get_builtin(&cmd));
        // todo: handle builtins the same way as bash... fork always, still handle bg (&)
    }
}
