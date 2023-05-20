#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/types.h>
#define DELIM " ,!¡¿?\'\"\n"

/* print functions */
int _putchar(char c);
int print_str(char *str);

/*handle string */
int _strlen(char *str);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
int _strncmp(char *s1, char *s2, int n);

/*handle errors*/
void handle_error(char *cmd_line); 

/*Tokenizing a line*/
char **lexical_analysis(char *input);

void *_calloc(unsigned int num, unsigned int size);

#endif
