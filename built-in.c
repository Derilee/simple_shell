#include "shell.h"
/**
 * implement_built_in - to check the built in function
 * @str: the string input
 * @strput: the string output
 * @line: string line
 */

int implement_built_in(char **str, int strput, char *line)
{
	int index = 0, size;
	char *env;
	char *_sys[] = {"exit", "env"};
	extern char **environ;

	if (!_strcmp(_sys[0], str[0]))
	{
		free(str);
		free(line);
		exit(strput);
	}
	else if (!_strcmp(_sys[1], str[0]))
	{
		while (environ[index] != NULL)
		{
			env = environ[index++];
			size = _strlen(env);
			write(STDOUT_FILENO, env, size);
			write(STDOUT_FILENO, "\n", 1);
		}
	}
	return 0;
}

/**
 * interface_built_in - to check the built in function
 * @str: the string input
 * @strput: the string output
 * @line: string line
 */
int interface_built_in(char **str, int strput, char *line)
{
	char *_sys[] = {"exit", "env"};

	if (!str || !*str)
		return 1;
	else if (!_strcmp(str[0], _sys[0]) || !_strcmp(str[0], _sys[1]))
		return implement_built_in(str, strput, line);
	else
		return comp_Arg(str, strput);
}
