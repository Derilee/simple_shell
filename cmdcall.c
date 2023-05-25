#include "shell.h"

/**
 * checkpath - checks the path
 * @av: arguments
 * Return: 1
 */
int checkpath(char *av[])
{
	char *path, *pathptr, *pathvar, *ptr, *pathenv = "PATH", *linect;
	int pathlen, cmdlen;

	for (ptr = av[0], cmdlen = 0; *ptr != 0; ptr++)
		cmdlen++;
	pathvar = fetchenv(pathenv);
	if (pathvar != pathenv)
	{
		pathenv = pathvar;
		while (*pathvar != 0)
		{
			for (pathlen = 0, ptr = pathvar; *ptr != 0 && *ptr != ':'; ptr++)
				pathlen++;
			path = malloc(sizeof(char) * (cmdlen + pathlen + 2));
			if (path == NULL)
			{
				free(pathenv);
				return (-1);
			}
			pathptr = path;
			while (*pathvar != ':' && *pathvar != 0)
				*pathptr++ = *pathvar++;
			if (pathptr != path)
				*pathptr++ = '/';
			ptr = av[0];
			while (*ptr != 0)
				*pathptr++ = *ptr++;
			*pathptr = 0;
			if (!access(path, F_OK))
			{
				pathlen = cmdcall(av, path);
				free(path);
				free(pathenv);
				return (pathlen);
			}
			free(path);
			if (*pathvar == ':')
				pathvar++;
		}
	}
	linect = itos(linecount(0));
	path = getsvar("0");
	fprintstrs(2, path, ": ", linect, ": ", av[0], ": not found\n", NULL);
	free(path);
	free(linect);
	if (pathenv != pathvar)
		free(pathenv);
	return (127);
}
/**
 * cmdcall - calls commands
 * @av: arguments
 * @cmd: command
 * Return: retval
 */
int cmdcall(char *av[], char *cmd)
{
	pid_t command;
	int status;
	char *linect, *dolz;

	environ = fetchallenv();
	if (environ == NULL)
		return (-1);
	command = fork();
	if (command == 0)
	{
		if (execve(cmd, av, *(fetchenviron())) == -1)
		{
			if (!access(cmd, F_OK))
			{
				printerr(NULL);
				exit(126);
			}
			else
			{
				linect = itos(linecount(0));
				dolz = getsvar("0");
				fprintstrs(2, dolz, ": ", linect, ": ", cmd, ": not found\n", NULL);
				free(dolz);
				free(linect);
				exit(127);
			}
			exit(1);
		}
	}
	else
	{
		wait(&status);
	}
	free(environ);
	return (status);
}
/**
 * builtincall - calls builtin commands
 * @av: arguments
 * Return: retval
 */
int builtincall(char *av[])
{
	int retval = 0;
	char *retstr;

	if (av[0] == NULL)
		return (0);
	if (!_strcmp(av[0], "exit"))
	{
		if (av[1] != NULL)
			if (av[1][0] >= '0' && av[1][0] <= '9')
			{
				retval = convertStrToInt(av[1]);
				exitcleanup(av);
				exitshellstate();
				exit(retval);
			}
			else
			{
				printerr(": exit: Illegal number: ");
				fprintstrs(STDERR_FILENO, av[1], "\n", NULL);
				retval = 2;
			}
		else
		{
			retstr = getsvar("?");
			retval = convertStrToInt(retstr);
			free(retstr);
			exitcleanup(av);
			exitshellstate();
			exit(retval);
		}
	}
	else if (!_strcmp(av[0], "cd"))
		retval = _cd(av);
	else if (!_strcmp(av[0], "history"))
		retval = printshellstate();
	else if (!_strcmp(av[0], "help"))
		retval = help(av[1]);
	else if (!_strcmp(av[0], "env"))
		retval = _printenv();
	else if (!_strcmp(av[0], "setenv"))
		retval = _setenv(av[1], av[2]);
	else if (!_strcmp(av[0], "unsetenv"))
		retval = _unsetenv(av[1]);
	else if (!_strcmp(av[0], "alias"))
		retval = aliascmd(av);
	else if (!_strcmp(av[0], "unset"))
		retval = unsetsvar(av[1]);
	else if (!_strcmp(av[0], "unalias"))
		retval = unsetalias(av[1]);
	else if (av[0][0] != '/' &&
		 !(av[0][0] == '.' && (av[0][1] == '/' ||
				       (av[0][1] == '.' && av[0][2] == '/'))))
		retval = checkpath(av);
	else
		retval = cmdcall(av, av[0]);
	if (retval % 256 == 0)
		retval /= 256;
	retstr = itos(retval % 128);
	setsvar("?", retstr);
	free(retstr);
	return (retval);
}
