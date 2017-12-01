#ifndef BASH_SHELL_H
#define BASH_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../exec_commands/exec_commands.h"
#include "../parser/parser.h"

int bash_shell();

void cnt_fork(char **);

char *rd_line();

void sighandler(int);

#endif