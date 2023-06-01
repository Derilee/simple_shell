#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>


extern char **environ;


/* main header */
int main(int argc, char *argv[], char **environ);


/* handle string and print string */
int _putchar(char c);
void _printstr(char *str);
size_t _strlen(char *str);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
char *_strncpy(char *dest, char *src, int n);
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);
int convertStrToInt(char *str);
char *itos(int digits);
char *_strchr(char *str, char ch);
int printfstr(int fd, char *str, ...);
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


/* handles the powershell and shell variables*/
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

int initializevars(int ac, char **str);
char *fetchvar(char *name);
int asgnvar(char *name, char *val);
int revokevar(char *name);

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
int clearalias(char *name);
int aliasmgt(char *argv[]);


/*cmd and path handler */
int chpath(char *argv[]);
int runcmd(char *argv[], char *cmd);
int invokecmd(char *argv[]);
int processcmd(char *cmd);


/* parse and arg handler */
char *processasgnvar(char *temp);
char *replacevars(char **temp);
char *filterarg(char *argc);
char *handlxpand(char *temp);
int transargs(char **buf);

/*shell ui handler*/
int inputchecker(char **temp, int fd);
int terminal(void);
int shellbatch(char *argv[]);


/*tokenization of string */
char *strtokenize(char *str, char *delim);
char *str_toks_quotes(char *str, char *delim, int esc);
int _cd(char *av[]);
void exitcleanup(char **av);


#endif
