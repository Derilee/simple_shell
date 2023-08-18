#include "main.h"
/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _printstr - function to print a string
 * @str: string to be printed
 * Return: printed string
 */
void _printstr(char *str)
{
	while (*str != '\0')
	{
		_putchar(*str);
		str++;
	}
}

/**
 * fetchenviron - function to fetch environment
 * Return: environment address
 */

char ***fetchenviron(void)
{
	static char **environ;

	return (&environ);
}

/**
 * _printenv - function to print environ
 * Return: 0, if successful
 */
int _printenv(void)
{
	char **environ = *(fetchenviron());
	int num = 0;

	while (environ[num] != NULL)
	{
		_printstr(environ[num]);
		_putchar('\n');
		num++;
	}
	return (0);
}

/**
 * convertStrToInt - function that converts string to an integer value
 * @str : input string
 * Return: integer value, or
 *         undefined if the input string is not a valid integer
 */

int convertStrToInt(char *str)
{
	int index, num = 0, neg_val = 0;
	unsigned int value = 0, dex = 1;

	for (index = 0; str[index]; index++)
	{
		if ((str[index] > '9' || str[index] < '0') && num > 0)
			break;
		if (str[index] == '-')
			neg_val++;
		if (str[index] >= '0' && str[index] <= '9')
			num++;
	}
	index--;

	while (num--)
	{
		value += (str[index] - '0') * dex;
		dex *= 10;
		index--;
	}
	if (neg_val % 2 != 0)
	{
		value *= -1;
	}
	return (value);
}
