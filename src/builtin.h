#ifndef CAMSHELL_BUILTIN_H
#define CAMSHELL_BUILTIN_H

#include <stdlib.h>

typedef enum builtin {
    BUILTIN_NONE,
    BUILTIN_EXIT
} builtin;

void handle_builtin(builtin builtin);

#endif //CAMSHELL_BUILTIN_H
