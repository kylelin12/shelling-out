#include "exec_commands.h"

int exec_commands(char** parsedargs) {
    char **cmds;
    char **backcmds;

    int cmdslength, restofcmdslength;
    for (cmdslength = 0; parsedargs[cmdslength]; cmdslength+=1){}

    printf("\n cmdslength: %d\n", cmdslength);

    int i;
    for (i = 0; parsedargs[i]; i++) {
        if (strcmp(parsedargs[i],";") == 0) {
            restofcmdslength = cmdslength-i-1;
            cmds = malloc(i*8);
            backcmds = malloc(restofcmdslength*8);
            memcpy(cmds, parsedargs, i*8);
            memcpy(backcmds, parsedargs+i+1, restofcmdslength*8);
            int j = 0;
            if (fork() == 0) {
                execvp(cmds[0], cmds);
                exit(0);
            } else {
                wait(0);
                printf("\n");
                free(cmds);
                exec_commands(backcmds);
            }
            return 0;
        }
    }

    if (fork() == 0) {
        execvp(parsedargs[0], parsedargs);
        exit(0);
    } else {
        wait(0);
    }

    return 0;
}