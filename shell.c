#include "shell.h"
/**
 * main - main method that start shell.
 * Return: (0).
 */
int main(void)
{
	char **unit = NULL;
	char *str = NULL;
	int strput = 0;

	do
	{
		if (isatty(STDIN_FILENO))
		{
			write(STDOUT_FILENO, "#cisfun$ ", 10);
		}
		str = read_line();
		unit = lexical_analysis(str);
		strput = check_built_in(unit, strput, str);

		free(str);
		free(unit);
	} while(1);
	return (0);
}
