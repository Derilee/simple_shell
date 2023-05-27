#include "shell.h"
/**
 * linecount - function that count lines
 * @increment: int increment
 * Return: counted lines
 */
int linecount(int increment)
{
	static int count;

	count = count + increment;
	return (count);
}

/**
 * itos - converts integer to string
 * @digits: number entered
 * Return: a string
 */
char *itos(int digits)
{
	int count, index, neg, conv, digitTest;
	char *output;

	digitTest = digits;
	count = 0;
	neg = 0;
	if (digits == 0)
	{
		output = malloc(sizeof(char) * 2);
		output[0] = '0';
		output[1] = 0;
		return (output);
	}
	if (digits < 0)
	{
		neg = 1;
		count++;
	}
	while (digitTest != 0)
	{
		digitTest /= 10;
		count++;
	}
	output = malloc(sizeof(char) * count + 1);
	if (output == NULL)
		return (NULL);
	if (neg)
		output[0] = '-';
	digitTest = digits;
	for (index = count - 1; index >= 0 + neg; index--)
	{
		conv = digitTest % 10;
		output[index] = (conv < 0 ? -conv : conv) + '0';
		digitTest /= 10;
	}
	output[count] = '\0';
	return (output);
}

/**
 * printerr - function that print errors
 * @str: string
 * Return: 0, if successful
 */
int printerr(char *str)
{
	char *pathname, *numstr;

	pathname = fetchvar("0");
	numstr = itos(linecount(0));
	if (str != NULL)
	{
		printfstr(2, pathname, ": ", numstr, str, NULL);
	}
	else
	{
		printfstr(2, pathname, ": ", numstr, ": ", NULL);
		perror(NULL);
	}
	free(pathname);
	free(numstr);
	return (0);
}

/**
 * printfstr - print string
 * @fd: file descriptor
 * @str: string entered
 * Return: 0, if successful
 */
int printfstr(int fd, char *str, ...)
{
	va_list list;

	if (str == NULL)
		return (0);
	va_start(list, str);
	write(fd, str, _strlen(str));
	str = va_arg(list, char *);
	while (str != NULL)
	{
		write(fd, str, _strlen(str));
		str = va_arg(list, char *);
	}
	return (0);
}

/**
 * _strchr - function that locates a character in a string
 * @str: char pointer
 * @ch: char
 * Return: a pointer address of first occurence of c in s
 */
char *_strchr(char *str, char ch)
{
	int input, len;

	input = 0;
	while (str[input] != '\0')
	{
		len++;
		input++;
	}

	input = 0;
	while (input <= len)
	{
		if (str[input] == ch)
			return (str + input);
		input++;
	}
	return (0);
}
