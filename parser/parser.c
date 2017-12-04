#include "parser.h"

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