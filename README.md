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

* <del>`echo <STRING>` Where STRING is really long cuts off and ends the
echo with an exclaimation mark.</del> **FIXED**

### Files & Function Headers:

* parser.c : Parses the line
```
    /*======== char **parseargs() ==========
    Inputs: char *line
    Returns: Array of strings where each string is an argument of the command

    Dynamically allocates memory for a string array and for a copy of the input line.

    Iterates through a copy of the input line and uses strsep to find the ` ` space
    delimiter. The index by index, each returned pointer from strsep is places in
    consecutive indexes of the string array. 

    Returns the string array.
    ====================*/
```
* exec_commands.c : Executes commands
```
    /*======== int exec_commands() ==========
    Inputs: char **parsedargs
    Returns: 0

    Recursively goes through the input string array and executes commands based on
    the detection of either `;`, `>`, `<`, or `|` in the array.

    If nothing goes wrong, 0 is returned.
    ====================*/
```
* bash_shell.c : Reads from stdin and executes commands using exec_commands()
```
    /*======== int bash_shell() ==========
    Inputs: 
    Returns: 0 

    If nothing goes wrong, 0 is returned.
    ====================*/
```
* shell.c : Main file to run. Contains loop to run bash_shell()
```
    /*======== int main() ==========
    Inputs: 
    Returns: 0

    If nothing goes wrong, 0 is returned.
    ====================*/
```