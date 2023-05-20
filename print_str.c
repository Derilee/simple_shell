#include "shell.h"
/**
* _putchar - writes the character c to stdout
* @c: The character to print
* Return: On sucess 1.
* On error, -1 is returned, and error is set appropriately.
*/
int _putchar(char c)
{
	return (write(1, &c, 1));
}

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
	return (c);
}
