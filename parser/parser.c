#include "parser.h"

/*======== char **parseargs() ==========
    Inputs: char *line, char *dlim
    Returns: Array of strings where each string is an argument of the command

    Dynamically allocates memory for a string array and for a copy of the input line.

    Iterates through a copy of the input line and uses strsep to find the delimiter. 
    Then index by index, each returned pointer from strsep is places in
    consecutive indexes of the string array. 

    Returns the string array.
    ====================*/

char **parseargs(char *line, char *dlim) {
    
    int linelen = strlen(line);

    char **parsedargs = (char **)malloc(sizeof(char *) * 8);

    char *linedupe = (char *)malloc(linelen);
    strncpy(linedupe, line, linelen);
    
    if (parsedargs) {
        int cmdcnt = 0;

        while (linedupe) {
            parsedargs[cmdcnt] = (char *)malloc(strlen(linedupe));
            /* strcpy is safe here because parsedargs[cmdcnt] will always be bigger than what the
               strsep() function returns here. */
            strcpy(parsedargs[cmdcnt], strsep(&linedupe, dlim)); 
            cmdcnt++;
        }
    }

    free(linedupe);

    return parsedargs;
}