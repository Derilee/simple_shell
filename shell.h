#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdarg.h>
#include <dirent.h>


extern char **environ;


/* handle string and print string */
int _putchar(char c);
void _printstr(char *str);
size_t _strlen(char *str);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);
int convertStrToInt(char *str);
char *itos(int digits);
char *_strchr(char *s, char c);
int fprintstrs(int fd, char *str, ...);
int printerr(char *);
int linecount(int);


/*handle env and print environment */
char ***fetchenviron(void);
int _printenv(void);
int modallenv(char **env, char *val);
char **fetchallenv(void);
char *fetchenv(char *details);
int _setenv(char *variable, char *value);
int _unsetenv(char *variable);


/* handles the powershell*/
/**
 * struct PowerShell - Struct PowerShell to list node
 * @variable: name of the variable
 * @value: value of the variable 
 * @dest: destination of the next variable in the list
 */
typedef struct PowerShell
{
        char *variable;
        char *value;
        struct PowerShell *dest;
} PowerShell;

PowerShell **fetchvariable(void);
PowerShell **fetchvalue(void);


void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int _getline(char **lineptr, int fd);
char *_getpid(void);


/* handles and print shell state history*/
/**
 * struct ShellState - struct shellstate to linked list node
 * @cmd: command line entered on the shell
 * @dest: pointer to the destination of the next node
 */

typedef struct ShellState
{
        char *cmd;
        struct ShellState *dest;
} ShellState;

ShellState **getshellstate();
int setshellstate(char *cmd);
int printshellstate(void);
int exitshellstate(void);


/* handles and print alias*/
/**
 * struct alias - Prints a list of all aliases, one per line,
 *                in the form name='value'
 * @name: defines an alias
 * @value: given value
 * @dest: pointer to destination of the  next node
 */

typedef struct alias
{
        char *name;
        char *value;
        struct alias *dest;
} alias;

alias **fetchall();
char *fetchalias(char *name);
int printalias(char *name, char *val);
int unsetalias(char *name);
int aliascmd(char *av[]);


/*cmd and path handler */
int chpath(char *av[]);
int builtincall(char *av[]);
int cmdcall(char *av[], char *path);
int help(char *cmd);


char *parsesetsvar(char *buf);
int parseargs(char **buf);
char *subsvars(char **buf);
char *cleanarg(char *arg);
char *tildeexpand(char *buf);

/*main header with needed fucntions*/
int inputvalidator(char **buf, int fd);
int shintmode(void);
int scriptmode(char *av[]);
int main(int ac, char *av[], char **environ);


/* handle shell veriables */
int initializevars(int ac, char **str);
char *getsvar(char *name);
int setsvar(char *name, char *val);
int unsetsvar(char *name);

/*tokenization of string */
char *strtok(char *str, char *delim);
char *strtokqe(char *str, char *delim, int escflags);
int _cd(char *av[]);
void exitcleanup(char **av);


#endif
