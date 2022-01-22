#include <string.h>
#include <stdio.h>
#include "jobs.h"
#include "command.h"

static job jobs[MAX_JOBS];

static size_t next_job_id = 1;

static void copy_command_string(const command *cmd, char buf[BUFFER_SIZE]) {
    char *buf_pos = buf;
    size_t argc = cmd_get_argc(cmd);
    char * const *argv = cmd_get_argv(cmd);

    for (size_t i = 0; i < argc; i++) {
        const char *arg = argv[i];
        size_t arg_len = strlen(arg);
        for (size_t j = 0; j < arg_len; j++) {
            *buf_pos++ = *arg++;
        }
        *buf_pos++ = ' ';
    }
}

void jobs_init() {
    for (size_t i = 0; i < MAX_JOBS; i++) {
        jobs[i].jid = 0;
    }
}

void jobs_add(pid_t pid, command *cmd) {
    // todo: ensure there aren't more than MAX_JOBS jobs
    size_t jid = next_job_id++; // todo: add more robust jid selection

    job *j = &jobs[jid];
    j->pid = pid;
    j->jid = jid;
    j->is_bg = cmd_is_bg_job(cmd);
    copy_command_string(cmd, j->command);
}

void jobs_print() {
    for (size_t i = 0; i < next_job_id; i++) {
        job j = jobs[i];
        if (j.jid != 0) {
            printf("[%zu] %d    %s    %s\n", j.jid, j.pid, "TODO", j.command);
        }
    }
}

