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
	int complete = 0;

	linecount(1);
	if (*ptr == 0)
		return (0);

	while (*ptr)
	{
		while ((*ptr == ' ' || *ptr == '\n') && !(complete & 3))
			ptr++;

		if (*ptr == 0)
			break;

		if (complete & 7)
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
