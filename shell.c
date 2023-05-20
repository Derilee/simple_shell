#include "shell.h"

/**
 * main - start shell.
 *
 * Return: (0).
 */

int main(void)
{
	char *row = NULL;
	char **tokens = NULL;
/**	int ct_output = 0;
*/
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#cisfun$ ", 10);

		row = read_line();
		tokens = lexical_analysis(row);
	/**	ct_output = check_built-in(tokens, ct_output, row);
*/
		free(row);
		free(tokens);
	}

	return (0);
}
