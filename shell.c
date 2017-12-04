#include "shell.h"

/*======== int main() ==========
    Inputs: 
    Returns: 0

    Intercepts SIGINT and passes it to sighandler()
    Continously runs the bash_shell()
    If nothing goes wrong, 0 is returned.
    ====================*/

int main() {

    signal(SIGINT, sighandler);

    while (1) {
        printf(">");
        bash_shell();
    }

    return 0;
}