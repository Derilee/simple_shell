#include "shell.h"
/**
 * print_str - function to print a string
 * @str: the string to be printed
 * Return: printed characters
 */
int print_str(char *str)
{
	int c;

	for (c = 0; str[c] != '\0'; c++)
	{
		_putchar(str[c]);
	}
	return c;
}

/**
 * _strlen - function to calculate the length of a string
 * @str: the string to be counted
 * Return: the length of the string
 */
int _strlen(char *str)
{
	int len = 0;

	for (; *str != '\0'; str++)
	{
		len++;
	}
	return (len);
}

/**
 * _strdup - function to duplicate a string
 * @str: string to be duplicated
 * Return: a pointer to the dduplicated string
 */
char *_strdup(char *str)
{
	if (!str)
		return (NULL);

	int copy = 0;

	while (str[copy])
		copy++;

	char *new_str = _calloc((sizeof(char) * (copy + 1)), 1);
	if (!new_str)
		return (NULL);

	for (int index = 0; index <= copy; index++)
		new_str[index] = str[index];

	return (new_str);
}

char *_strcat(char *dest, char *src, char *val)
{
	
