#include "shell.h"
/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _printenv - print environment
 * Return: 0 if success
 */
int _printenv(void)
{
	char **environ = *(getenviron());
	int i;
	int j;

	i = 0;
	while (environ[i])
	{
		j = 0;
		while (environ[i][j] != 0)
		{
			_putchar(environ[i][j]);
			j++;
		}
		_putchar('\n');
		i++;
	}
	return (0);
}

/**
 * getenviron - static wrapper copy whole environ
 *
 * Return: environ address
 */

char ***getenviron()
{
	static char **environ;

	return (&environ);
}

/**
 * _atoi - converts string to number
 * @s : pointer int
 * _atoi: converts string to number
 * Return: The result (converted number)
 */

int _atoi(char *s)
{
	int i;
	int check_num;
	unsigned int sum;
	unsigned int x;
	int neg;

	neg = 0;
	check_num = 0;
	sum = 0;
	i = 0;

	/* run a while loop */
	while (s[i] != '\0')
	{
		if ((s[i] > '9' || s[i] < '0') && check_num > 0)
			break;
		if (s[i] == '-')
			neg++;
		if (s[i] >= '0' && s[i] <= '9')
			check_num++;
		i++;
	}
	i = i - 1;
	x = 1;
	while (check_num > 0)
	{
		sum = sum + ((s[i] - '0') * x);
		x = x * 10;
		i--;
		check_num--;
	}
	if (neg % 2 != 0)
		sum = sum * -1;
	return (sum);
}
