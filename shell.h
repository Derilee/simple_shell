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

/* handle string and print environment */
int _putchar(char c);
void _printstr(char *str);
char ***fetchenviron(void);
int _printenv(void);
int convertStrToInt(char *str);

/* handle string */
size_t _strlen(char *str);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);

int modallenv(char **env, char *val);
char **fetchallenv(void);
char *fetchenv(char *details);

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
 * struct ShellVar - shellvar list node
 * @name: name of variable
 * @val: value of variable
 * @next: next variable in the list
 */
typedef struct ShellVar
{
        char *name;
        char *val;
        struct ShellVar *next;
} ShellVar;


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

/* from _getenv.c and getenviron.c */
int _setenv(char *name, char *val);
int _unsetenv(char *name);


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
ShellVar **getspecial(void);
ShellVar **getvars(void);

/* from _realloc.c */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* from _strtok.c */
char *strtok(char *str, char *delim);

/* from _getline.c */
int _getline(char **lineptr, int fd);

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

char *_getpid(void);


#endif
