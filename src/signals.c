#include <cam/sys/signal.h>
#include "signals.h"
#include "jobs.h"

static void signals_forwarding_handler(int signum) {
    signals_block(); // block signals to be async-signal-safe when accessing global variables
    job *job = jobs_get_fg_job();
    signals_unblock();

    if (job == NULL) {
        return;
    }

    cam_kill(-job->pid, signum); // forward signal to fg process group
}

static void signals_sigchld_handler() {

}

void signals_install_handlers() {
    cam_signal(SIGINT, signals_forwarding_handler);
    cam_signal(SIGTSTP, signals_forwarding_handler);
    cam_signal(SIGCHLD, signals_sigchld_handler);
}

void signals_block() {
    sigset_t set;

    cam_sigemptyset(&set);
    cam_sigaddset(&set, SIGINT);
    cam_sigaddset(&set, SIGTSTP);
    cam_sigaddset(&set, SIGCHLD);

    cam_sigprocmask(CAM_SIGHOW_BLOCK, &set, NULL);
}

void signals_unblock() {
    sigset_t set;

    cam_sigemptyset(&set);
    cam_sigaddset(&set, SIGINT);
    cam_sigaddset(&set, SIGTSTP);
    cam_sigaddset(&set, SIGCHLD);

    cam_sigprocmask(CAM_SIGHOW_UNBLOCK, &set, NULL);
}
