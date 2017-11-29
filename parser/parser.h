#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Takes a character pointer, a string, and parses it into a character array pointer
char **parseargs(char *);

#endif