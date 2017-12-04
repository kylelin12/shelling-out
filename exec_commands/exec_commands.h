#ifndef EXEC_COMMANDS_H
#define EXEC_COMMANDS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <ctype.h>

#include "../parser/parser.h"

void exec_commands(char *);
char *snipsnip(char *);
void exec_fork(char **);
void exec_special(char *, int);

int token_checker(char *);
#endif