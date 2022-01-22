#define _GNU_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <cam/sys/process.h>
#include <cam/error.h>
#include "evaluate.h"
#include "consts.h"
#include "parse.h"
#include "command.h"
#include "jobs.h"

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

    // handle builtins immediately
    builtin builtin = cmd_get_builtin(&cmd);
    if (builtin != BUILTIN_NONE) {
        handle_builtin(builtin);
        return;
    }

    // todo: block signals around this -> prevent race condition where child process terminates and we handle the resulting SIGCHLD before adding job to list / waiting

    // run command in child process
    pid_t pid;
    if ((pid = cam_fork()) == 0) { // child process
        // todo: unblock signals
        // todo: restore signal handlers to default

        char * const *argv = cmd_get_argv(&cmd);
        // todo: add execvpe to libcam
        if (execvpe(argv[0], argv, environ) < 0) {
            printf("%s: Command not found.\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    } else { // parent process
        jobs_add(pid, &cmd);
    }

    // todo: unblock signals

    // wait for command if not background
    if (cmd_is_fg_job(&cmd)) {
        int status;
        if (waitpid(pid, &status, 0) < 0) {
            cam_handle_unix_error("waitpid error");
        }
    } else {
        printf("%d, %s", pid, buffer);
    }
}
