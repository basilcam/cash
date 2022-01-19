#ifndef CAMSHELL_PARSE_H
#define CAMSHELL_PARSE_H

#include "command.h"

void parse_argv_argc(char *buffer, char **argv, size_t *argc);

bool parse_bg(char **argv, size_t argc);

builtin parse_builtin(char **argv);

#endif // CAMSHELL_PARSE_H