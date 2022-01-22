#ifndef CAMSHELL_JOBS_H
#define CAMSHELL_JOBS_H

#include <unistd.h>
#include <stdbool.h>
#include "consts.h"
#include "command.h"

typedef struct {
    char command[BUFFER_SIZE];
    pid_t pid;
    size_t jid;
    bool is_bg;
} job;

void jobs_add(pid_t pid, command *cmd);

void jobs_print();

job *jobs_get_fg_job();

#endif // CAMSHELL_JOBS_H
