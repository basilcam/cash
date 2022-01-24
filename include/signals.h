#ifndef CAMSHELL_SIGNALS_H
#define CAMSHELL_SIGNALS_H

void signals_install_handlers();

void signals_uninstall_handlers();

void signals_block();

void signals_unblock();

void signals_resume(pid_t pid);

#endif // CAMSHELL_SIGNALS_H
