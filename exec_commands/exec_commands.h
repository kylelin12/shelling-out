#ifndef EXEC_COMMANDS_H
#define EXEC_COMMANDS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int exec_commands(char **);

int token_checker(char *);
#endif