#include "shell.h"
/**
 * inputchecker - checks input characters
 * @temp: temporary storage to store char
 * @fd: file descriptor
 * Return: 0 if successful
 */
int inputchecker(char **temp, int fd)
{
	char *newstr, *input, *ptr = *temp;
	ssize_t total;
	size_t len;
	int comp = 0;

	linecount(1);
	if (*ptr == 0)
		return (0);

	while (*ptr)
	{
		while ((*ptr == ' ' || *ptr == '\n') && !(comp & 3))
			ptr++;

		if (*ptr == 0)
			break;

		if (comp & 7)
		{
			input = NULL;
			if (isatty(fd))
				printfstr(1, ">", NULL);

			total = _getline(&input, fd);
			if (total == 0 && !isatty(fd))
			{
				free(*temp);
				free(input);
				printerr(": Syntax error: unterminated quoted string\n");
				return (-1);
			}
			if (total == -1)
			{

			}
			len = _strlen(*temp);
			newstr = malloc(len + total + 1);
			_strcpy(newstr, *temp);
			_strcpy(newstr + len, input);
			free(*temp);
			free(input);
			return (inputchecker(&newstr, fd));
		}
		setshellstate(*temp);
		return (transargs(temp));
	}
	return (0);
}

/**
 * terminal - function that handles terminal mode ui
 * Return: result
 */
int terminal(void)
{
	char *str = NULL, *pwd;
	ssize_t len = 0, endofline = 0, result = 0;
	int istty = isatty(0) && isatty(1);
	char hostname[256];

	while (!endofline)
	{
		if (istty)
		{
			pwd = fetchenv("PWD");
			if (pwd != NULL)
			{
			if (gethostname(hostname, sizeof(hostname)) == 0)
			{
				printfstr(1, "root@", hostname, ":", pwd, "$ ", NULL);
				free(pwd);
			}
			}
			else
			{
				printfstr(1, "root@", hostname, "$ ", NULL);
			}
		}
		len = _getline(&str, STDIN_FILENO);
		if (len == 0 || len == -1)
		{
			free(str);
			break;
		}
		if (str[len -1] != '\n')
			endofline = 1;

		result = inputchecker(&str, STDIN_FILENO);
		str = NULL;

		if (endofline)
			break;
	}
	return (result);
}
