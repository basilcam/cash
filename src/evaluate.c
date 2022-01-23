#define _GNU_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <cam/sys/process.h>
#include <cam/sys/signal.h>
#include "evaluate.h"
#include "consts.h"
#include "parse.h"
#include "command.h"
#include "jobs.h"
#include "signals.h"

void wait_on_fg_job(job *j) {
    sigset_t set;
    cam_sigemptyset(&set);

    // wait for fg job to finish
    while (job_get_state(j) == JOB_STATE_FG)
    {
        cam_sigsuspend(&set);
    }
}

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
        builtin_handle(builtin);
        return;
    }

    signals_block();

    // run command in child process
    pid_t pid;
    if ((pid = cam_fork()) == 0) { // child process
        signals_uninstall_handlers();
        signals_unblock();
        setpgrp(); // shouldn't be in same process group as shell

        char * const *argv = cmd_get_argv(&cmd);

        // todo: add execvpe to libcam
        if (execvpe(argv[0], argv, environ) < 0) {
            printf("%s: Command not found.\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    job *j = jobs_add(pid, &cmd);

    // wait for command if not background
    if (cmd_is_fg_job(&cmd)) {
        signals_unblock();
        wait_on_fg_job(j);
    } else {
        printf("%d, %s", job_get_pid(j), job_get_command(j));
        signals_unblock();
    }
}
