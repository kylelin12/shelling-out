#include "parser.h"

char **parseargs(char *line) {
    
    char **parsedargs = (char **)malloc(sizeof(char *) * 8);

    char *linedupe = (char *)malloc(sizeof(line));
    strcpy(linedupe, line);
    
    if (parsedargs) {
        int cmdcnt = 0;

        while (linedupe != NULL) {
            parsedargs[cmdcnt] = malloc(sizeof(*parsedargs[cmdcnt]) * 8);
            strcpy(parsedargs[cmdcnt], strsep(&linedupe, " "));
            cmdcnt++;
        }
    }

    free(linedupe);

    return parsedargs;
}