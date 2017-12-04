# Shelling Out - Shell in C

by Kyle Lin

### Features:

* Forks children and executes commands from them
* Parses multiple commands in one line seperated by a `;`
* exit
* cd
* Signal handling
* Redirection using >, <
* Piping using |

### Attempt(ed/ing):

* Handling `CTRL + Z` aka SIGTSTP signal

### Bugs:

* <del>`echo <STRING>` Where STRING is really long cuts off and ends the
echo with an exclaimation mark.</del> **FIXED**
* Handling SIGTSTP doesn't work. After sending the SIGTSTP signal, program
starts repeatedly sending ">" to stdout.
* Randomly sends to STDOUT more than once because it forks more than once?
* When creating or deleting files, the "No such file/directory" error is returned
although the file is successfully added/removed.
* Piping and using flags isn't compatible. Ex: `ps -aux | wc` won't work properly.

### Files & Function Headers:

* parser.c : Parses the line with the given delimiter
```
    /*======== char **parseargs() ==========
    Inputs: char *line, char *dlim
    Returns: Array of strings where each string is an argument of the command

    Dynamically allocates memory for a string array and for a copy of the input line.

    Iterates through a copy of the input line and uses strsep to find the delimiter. 
    Then index by index, each returned pointer from strsep is places in
    consecutive indexes of the string array. 

    Returns the string array.
    ====================*/
```
* exec_commands.c : Executes commands
```
    /*======== void exec_commands() ==========
    Inputs: char *cmds
    Returns: 

    Takes an input string from rd_line and determines
    whether to pass it to the exec_form() function or
    the exec_special() function.
    ====================*/

    /*======== char *snipsnip() ==========
    Inputs: char *car
    Returns: char *

    Removes whitespace from the beginning or end of a string.
    ====================*/

    /*======== void exec_fork() ==========
    Inputs: char **parsedargs
    Returns: void

    Executes hardcoded exceptions for exit and cd if they are detected.
    Otherwise forks and allows the child to execute the command.
    ====================*/

    /*======== void exec_special() ==========
    Inputs: char *parsedargs, int token
    Returns: void

    Takes a single command + its arguments and a token.
    The token tells the function whether to execute the
    ">", "<", or "|" path.
    ====================*/

    /*======== int token_checker() ==========
    Inputs: char *token
    Returns: int

    Checks if the input character is ";", ">", "<", or "|"
    and returns 1, 2, 3, 4 respectively.
    ====================*/
```
* bash_shell.c : Reads from stdin and executes commands using exec_commands()
```
    /*======== int bash_shell() ==========
    Inputs: 
    Returns: 0 

    Runs rd_line() to read a line from stdin.
    Passes the char* from rd_line() into exec_commands().
    Returns 0 if nothing goes wrong.
    ====================*/

    /*======== char *rd_line() ==========
    Inputs: 
    Returns: Char pointer containing the input string 

    Allocates memory to a char pointer.
    Uses fgets() to read from stdin to the char pointer.
    Returns the pointer.
    ====================*/

    /*======== void sighandler() ==========
    Inputs: int
    Returns: void 

    Takes an input int which is received from signal() in main().
    If SIGINT is the input, re-runs bash_shell() and clears the buffer.
    If SIGSTSP is the input, sends a SIGSTOP signal to the process. **Broken and removed**
    ====================*/
```
* shell.c : Main file to run. Contains loop to run bash_shell()
```
    /*======== int main() ==========
    Inputs: 
    Returns: 0

    Intercepts SIGINT and passes it to sighandler()
    Continously runs the bash_shell()
    If nothing goes wrong, 0 is returned.
    ====================*/
```