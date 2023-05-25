#include "shell.h"

/**
 * chpath - function that checks the path
 * @av: arguments passed
 * Return: 127 on success, -1 on failure
 */
int chpath(char *av[])
{
	char *path, *pathptr, *var, *ptr, *pathenv = "PATH", *cline;
	int pathlen, cmdlen;

	for (ptr = av[0], cmdlen = 0; *ptr != 0; ptr++)
		cmdlen++;
	var = fetchenv(pathenv);
	if (var != pathenv)
	{
		pathenv = var;
		while (*var != 0)
		{
			for (pathlen = 0, ptr = var; *ptr != 0 && *ptr != ':'; ptr++)
				pathlen++;
			path = malloc(sizeof(char) * (cmdlen + pathlen + 2));
			if (path == NULL)
			{
				free(pathenv);
				return (-1);
			}
			pathptr = path;
			while (*var != ':' && *var != 0)
				*pathptr++ = *var++;
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
			if (*var == ':')
				var++;
		}
	}
	cline = itos(linecount(0));
	path = getsvar("0");
	fprintstrs(2, path, ": ", cline, ": ", av[0], ": not found\n", NULL);
	free(path);
	free(cline);
	if (pathenv != var)
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
		retval = aliasmgt(av);
	else if (!_strcmp(av[0], "unset"))
		retval = unsetsvar(av[1]);
	else if (!_strcmp(av[0], "unalias"))
		retval = unsetalias(av[1]);
	else if (av[0][0] != '/' &&
		 !(av[0][0] == '.' && (av[0][1] == '/' ||
				       (av[0][1] == '.' && av[0][2] == '/'))))
		retval = chpath(av);
	else
		retval = cmdcall(av, av[0]);
	if (retval % 256 == 0)
		retval /= 256;
	retstr = itos(retval % 128);
	setsvar("?", retstr);
	free(retstr);
	return (retval);
}

/**
 * help - help builtin command
 * @cmd: the command line inserted
 * Return: 0 if sucess (always)
 */
int help(char *cmd)
{
	char *file;
	int fd, r;
	char *s;

	if (cmd == NULL)
	{
		s = "help: no builtin entered.\n";
		r = _strlen(s);
		r = write(1, s, r);
		return (0);
	}

	if (!_strcmp(cmd, "cd"))
	{
		file = "help_cd";
		fd = open(file, O_RDWR);
		s = malloc(256);
		if (s == NULL)
			return (-1);
		while ((r = read(fd, s, 256)) > 0)
		{
			r = write(1, s, r);
			if  (r == -1)
			{
				return (-1);
			}
		}
		free(s);
		fd = close(fd);
		return (0);
	}
	else if (!_strcmp(cmd, "history"))
	{
		file = "help_hist";
		fd = open(file, O_RDWR);
		s = malloc(256);
		if (s == NULL)
			return (-1);
		while ((r = read(fd, s, 256)) > 0)
		{
			r = write(1, s, r);
			if  (r == -1)
			{
				return (-1);
			}
		}
		free(s);
		fd = close(fd);
		return (0);
	}
	else if (!_strcmp(cmd, "help"))
	{
		file = "help_hel";
		fd = open(file, O_RDWR);
		s = malloc(256);
		if (s == NULL)
			return (-1);
		while ((r = read(fd, s, 256)) > 0)
		{
			r = write(1, s, r);
			if  (r == -1)
			{
				return (-1);
			}
		}
		free(s);
		fd = close(fd);
		return (0);
	}
	else if (!_strcmp(cmd, "alias"))
	{
		file = "help_al";
		fd = open(file, O_RDWR);
		s = malloc(256);
		if (s == NULL)
			return (-1);
		while ((r = read(fd, s, 256)) > 0)
		{
			r = write(1, s, r);
			if  (r == -1)
			{
				return (-1);
			}
		}
		free(s);
		fd = close(fd);
		return (0);
	}
	else if (!_strcmp(cmd, "unset"))
	{
		file = "help_unset";
		fd = open(file, O_RDWR);
		s = malloc(256);
		if (s == NULL)
			return (-1);
		while ((r = read(fd, s, 256)) > 0)
		{
			r = write(1, s, r);
			if  (r == -1)
			{
				return (-1);
			}
		}
		free(s);
		fd = close(fd);
		return (0);
	}
	else if (!_strcmp(cmd, "unalias"))
	{
		file = "help_unal";
		fd = open(file, O_RDWR);
		s = malloc(256);
		if (s == NULL)
			return (-1);
		while ((r = read(fd, s, 256)) > 0)
		{
			r = write(1, s, r);
			if  (r == -1)
			{
				return (-1);
			}
		}
		free(s);
		fd = close(fd);
		return (0);
	}
	else if (!_strcmp(cmd, "env"))
	{
		file = "help_env";
		fd = open(file, O_RDWR);
		s = malloc(256);
		if (s == NULL)
			return (-1);
		while ((r = read(fd, s, 256)) > 0)
		{
			r = write(1, s, r);
			if  (r == -1)
			{
				return (-1);
			}
		}
		free(s);
		fd = close(fd);
		return (0);
	}
	else if (!_strcmp(cmd, "setenv"))
	{
		file = "help_setenv";
		fd = open(file, O_RDWR);
		s = malloc(256);
		if (s == NULL)
			return (-1);
		while ((r = read(fd, s, 256)) > 0)
		{
			r = write(1, s, r);
			if  (r == -1)
			{
				return (-1);
			}
		}
		free(s);
		fd = close(fd);
		return (0);
	}
	else if (!_strcmp(cmd, "unsetenv"))
	{
		file = "help_unenv";
		fd = open(file, O_RDWR);
		s = malloc(256);
		if (s == NULL)
			return (-1);
		while ((r = read(fd, s, 256)) > 0)
		{
			r = write(1, s, r);
			if  (r == -1)
			{
				return (-1);
			}
		}
		free(s);
		fd = close(fd);
		return (0);
	}
	else
	{
		s = "help: no help topics match.\n";
		r = _strlen(s);
		r = write(1, s, r);
		return (0);
	}
}
