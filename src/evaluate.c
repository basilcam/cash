#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cam/sys/process.h>
#include <sys/wait.h>
#include "evaluate.h"
#include "consts.h"
#include "parse.h"

extern char **environ;

void evaluate(char *buffer) {
    char *argv[MAX_ARGS];
    char buf[BUFFER_SIZE];
    int bg;
    pid_t pid;

    strcpy(buf, buffer);
    bg = parseline(buf, argv);

    // ignore empty lines
    if (argv[0] == NULL) {
        return;
    }

    if (!is_builtin_command(argv)) {
        // execute command in child process
        if ((pid = cam_fork()) == 0) {
            if (execve(argv[0], argv, environ) < 0) {
                printf("%s: Command not found.\n", argv[0]);
                exit(EXIT_SUCCESS);
            }
        }

        // wait for command if not background
        if (!bg) {
            int status;
            if (waitpid(pid, &status, 0) < 0) {
                cam_handle_unix_error("waitfg: waitpid error");
            }
        } else {
            printf("%d, %s", pid, buffer);
        }
    }
}
