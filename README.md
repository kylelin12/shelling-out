# Shelling Out - Shell in C

by Kyle Lin

### Features:

* Forks and executes commands
* Parses multiple commands in one line
* Exits

### Attempt(ed/ing):

* Redirection using >, <
* Piping using |

### Bugs:

* `echo <STRING>` Where STRING is really long cuts off and ends the
echo with an exclaimation mark.

### Files & Function Headers:

* parser.c : Contains line parsing functions
```
    /*======== char **parseargs() ==========
    Inputs: char *line
    Returns: Array of strings where each string is an argument of the command
    ====================*/
```
* exec_commands.c :