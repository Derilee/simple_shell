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
