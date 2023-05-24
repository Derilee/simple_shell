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

/*#define _GNU_SOURCE*/

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


/*handle env and print environment */
char ***fetchenviron(void);
int _printenv(void);
int modallenv(char **env, char *val);
char **fetchallenv(void);
char *fetchenv(char *details);
int _setenv(char *variable, char *value);
int _unsetenv(char *variable);


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



/* from in.c */
int shintmode(void);


/**
 * struct HistList - singly linked list
 * @cmd: command line entered
 * @next: pointer to the next node
 * Description: singly linked list node structure for History 
 * for Holberton project
 */

typedef struct HistList
{
        char *cmd;
        struct HistList *next;
} HistList;


/**
 * struct AliasData - struct for alias function
 * @AliasData - name of the struct
 * @name: name of the alias value
 * @val: value for the alias
 * @next: pointer to next node
 *
 */

typedef struct AliasData
{
        char *name;
        char *val;
        struct AliasData *next;
} AliasData;



/* from _printenv.c */

/* from cmdcall.c */
int builtincall(char *av[]);
int cmdcall(char *av[], char *path);

/* from parser.c */
int parseargs(char **buf);

/* from errhandl.c */
int errhandl(int status);



/* from utility.c */
char *itos(int digits);
char *_strchr(char *s, char c);
int fprintstrs(int fd, char *str, ...);
int printerr(char *);
int linecount(int);

/* from cd.c */
int _cd(char *av[]);

/* from alias.c */
int aliascmd(char **av);
char *getalias(char *name);
int unsetalias(char *name);

/* from shellvars.c */
int initsvars(int ac, char **av);
char *getsvar(char *name);
int setsvar(char *name, char *val);
int unsetsvar(char *name);


/* from _strtok.c */
char *strtok(char *str, char *delim);


char *strtokqe(char *str, char *delim, int escflags);

/*from history.c*/
int sethist(char *cmd);
int print_hist(void);
int exit_hist(void);


/* from _printenv.c */


/*from help.c*/
int help(char *cmd);

/* from exitcleanup.c */
void exitcleanup(char **av);



#endif
