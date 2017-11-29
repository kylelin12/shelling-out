#include "bash_shell.h"

int bash_shell() {
    unsigned int childpid;
    char *inputcmd = malloc(256);
    fgets(inputcmd, 256, stdin);
    int length = strlen(inputcmd);

    if (length > 0 && inputcmd[length - 1] == '\n') {
        inputcmd[length - 1] = '\0';
    }

    char **commands = parseargs(inputcmd);

    if (strcmp(commands[0], "cd") == 0) {
        chdir(commands[1]);
    } else if (strcmp(commands[0], "exit") == 0) {
        exit(0);
    }

    childpid = getpid();
    printf("CHILD: my id is: %du\n", childpid);

    exec_commands(commands);

    return 0;
}