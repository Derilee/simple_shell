#include "shell.h"
/**
 * read_line - function that reads the command line
 * Return: read line
 */
char *read_line(void)
{
	int line = 0;
	char *buffer = NULL;
	size_t size = 0;
	line = getline(&buffer, &size, stdin);

	if (line == EOF)
	{
		free(buffer);

		if (isatty(STDIN_FILENO))
		{
			write(STDOUT_FILENO, "\n", 1);
		}
		exit(EXIT_SUCCESS);
	}
	return (buffer);
}
