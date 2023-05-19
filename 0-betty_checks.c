#include "shell.h"
/**
 * print_alphabet - function to print an alphabet
 *
 * Return: Always(c) Success
 *
 * description: A code that passes the betty checks
 */
int print_alphabet(void)
{
	char c = 'a';

	while (c <= 'z')
	{
		_putchar(c);
		c++;
	}
	_putchar('\n');
	return (c);
}
