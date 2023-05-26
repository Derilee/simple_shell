#include "shell.h"
/**
 * runcmd - function that calls and runs cmd commands
 * @argv: arguments passed
 * @cmd: command passed
 * Return: called cmd command
 */
int runcmd(char *argv[], char *cmd)
{
	pid_t input;
	char *cline, *var;
	int cprocess;
	char **environ = fetchallenv();
	
	if (environ == NULL)
		return (-1);

	input = fork();
	if (input == 0)
	{
		if (execve(cmd, argv, *(fetchenviron())) == -1)
		{
			if (!access(cmd, F_OK))
			{
				printerr(NULL);
				exit(126);
			}
			else
			{
				cline = itos(linecount(0));
				var = getsvar("0");
				printfstr(2, var, ": ", cline, ": ", cmd, ": not found\n", NULL);
				free(var);
				free(cline);
				exit(127);
			}
			exit(1);
		}
	}
	else
	{
		wait(&cprocess);
	}
	free(environ);
	return (cprocess);
}

/**
 * chpath - function that checks the path
 * @av: arguments passed
 * Return: 127 on success, -1 on failure
 */
int chpath(char *argv[])
{
	int clen = 0, plen;
	char *pathenv = "PATH", *var = fetchenv(pathenv);
	char *ptr, *cline, *path, *pathptr;

	for (ptr = argv[0]; *ptr != 0; ptr++)
		clen++;
	if (var != pathenv)
	{
		pathenv = var;
		while (*var != 0)
		{
			plen = 0;
			for (ptr = var; *ptr != 0 && *ptr != ':'; ptr++)
				plen++;
			path = malloc(sizeof(char) * (clen + plen + 2));
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
			ptr = argv[0];
			while (*ptr != 0)
				*pathptr++ = *ptr++;
			*pathptr = 0;
			if (!access(path, F_OK))
			{
				plen = runcmd(argv, path);
				free(path);
				free(pathenv);
				return (plen);
			}
			free(path);
			if (*var == ':')
				var++;
		}
	}
	cline = itos(linecount(0));
	path = getsvar("0");
	printfstr(2, path, ": ", cline, ": ", argv[0], ": not found \n", NULL);
	free(path);
	free(cline);
	if (pathenv != var)
		free(pathenv);
	return (127);
}

/**
 * invokecmd - invokes cmd and calls builtin commands
 * @argv: arguments passed
 * Return: called builtin commands
 */
int invokecmd(char *argv[])
{
	char *str;
	int val = 0;

	if (argv[0] == NULL)
		return (0);
	if (!_strcmp(argv[0], "exit"))
	{
		if (argv[1] != NULL && argv[1][0] >= '0' && argv[1][0] <= '9')
		{
			val = convertStrToInt(argv[1]);
			exitcleanup(argv);
			exitshellstate();
			exit(val);
		}
		else if (argv[1] != NULL)
		{
			printerr(": exit: Invalid command: ");
			printfstr(STDERR_FILENO, argv[1], "\n", NULL);
			val = 2;
		}
		else
		{
			str = getsvar("?");
			val = convertStrToInt(str);
			free(str);
			exitcleanup(argv);
			exitshellstate();
			exit(val);
		}
	}
	else if (!_strcmp(argv[0], "cd"))
		val = _cd(argv);
	else if (!_strcmp(argv[0], "help"))
		val = processcmd(argv[1]);
	else if (!_strcmp(argv[0], "env"))
		val = _printenv();
	else if (!_strcmp(argv[0], "setenv"))
		val = _setenv(argv[1], argv[2]);
	else if (!_strcmp(argv[0], "unsetenv"))
		val = _unsetenv(argv[1]);
	else if (!_strcmp(argv[0], "alias"))
		val = aliasmgt(argv);
	else if (!_strcmp(argv[0], "unalias"))
		val = clearalias(argv[1]);
	else if (!_strcmp(argv[0], "history"))
		val = printshellstate();
	else if (argv[0][0] != '/' &&
		 !(argv[0][0] == '.' && (argv[0][1] == '/' ||
		(argv[0][1] == '.' && argv[0][2] == '/'))))
	{
		val = chpath(argv);
	}
	else
	{
		val = runcmd(argv, argv[0]);
	}
	if (val % 256 == 0)
		val /= 256;

	str = itos(val % 128);
	setsvar("?", str);
	free(str);
	return (val);
}

/**
 * processcmd - helps in processing builtin command
 * @cmd: the command line inserted
 * Return: 0 if sucess
 */
int processcmd(char *cmd)
{
	struct Cmdlist
	{
		char *file;
		char *cmdinfo;
	} helpCommands[] = {
		{"cd", "cmdHelp"},
		{"history", "historyHelp"},
		{"help", "help"},
		{"unset", "unsetHelp"},
		{"alias", "aliasHelp"},
		{"unalias", "unaliasHelp"},
		{"env", "envHelp"},
		{"setenv", "setenvHelp"},
		{"unsetenv", "help_unenv"}
	};

	char *str;
	int fd, rev;
	int inputcmd = sizeof(helpCommands) / sizeof(helpCommands[0]);
	int input;

	if (cmd == NULL)
	{
		str = "no builtin command entered.\n";
		rev = _strlen(str);
		rev = write(1, str, rev);
		return (0);
	}
	for (input = 0; input < inputcmd; input++)
	{
		if (!_strcmp(cmd, helpCommands[input].cmdinfo))
		{
			fd = open(helpCommands[input].file, O_RDWR);
			str = malloc(256);
			if (str == NULL)
				return (-1);
			while ((rev = read(fd, str, 256)) > 0)
			{
				rev = write(1, str, rev);
				if (rev == -1)
				{
					return (-1);
				}
			}
			free(str);
			fd = close(fd);
			return (0);
		}
	}
	str = "help: no help topics match.\n";
	rev = _strlen(str);
	rev = write(1, str, rev);
	return (0);
}
