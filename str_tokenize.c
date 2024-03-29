#include "main.h"
/**
* _strncpy - copy a string
* @dest: input value
* @src: input value
* @n: input value
* Return: dest
*/
char *_strncpy(char *dest, char *src, int n)
{
	int j;

	j = 0;
	while (j < n && src[j] != '\0')
	{
		dest[j] = src[j];
		j++;
	}
	while (j < n)
	{
		dest[j] = '\0';
		j++;
	}

	return (dest);
}

/**
 * strtokenize - tokenizes a string
 * @str: string to tokenize
 * @delim: delimiters used to create tokens
 * Return: tokenized string
 */
char *strtokenize(char *str, char *delim)
{
	static char *stdstr;
	char *tokstr = stdstr;
	char *input = delim;

	if (str != NULL)
		stdstr = str;
	if (stdstr == NULL || *stdstr == '\0')
		return (NULL);

	while (*stdstr != '\0')
	{
		while (*input != '\0')
		{
			if (*stdstr == *input)
			{
				*stdstr = '\0';
				stdstr++;
				return (tokstr);
			}
			input++;
		}
	stdstr++;
	}
	return (tokstr);
}
/**
 * strtokqe - string token with quotes and escapes
 * @str: string token to be quoted
 * @delim: delimiters
 * @escflags: escape flags
 * flags are bitwise.
 * 1 = use \ to escape delims
 * 2 = single quote skips
 * 4 = double quote skips
 * Return: string
 */
char *strtokqe(char *str, char *delim, int escflags)
{
	static char *saved_string;
	int i;
	int j;

	if (str == 0)
		str = saved_string;
	if (str == 0)
		return (0);

	i = 0;
	while (str[i] != 0)
	{
		j = 0;
		while (delim[j] != 0)
		{
			if (str[i] == delim[j])
				break;
			j++;
		}
		if (delim[j] == 0)
			break;
		i++;
	}
	str = str + i;
	if (*str == 0)
	{
		saved_string = str;
		return (0);
	}

	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == '\\' && escflags & 1)
		{
			if (str[i + 1] != 0)
				i++;
			i++;
			continue;
		}
		if (str[i] == '\'' && escflags & 2)
		{
			i++;
			while (str[i] != '\'')
			{
				if (str[i] == '\\' && escflags & 1)
				{
					if (str[i + 1] != 0)
						i++;
					i++;
					continue;
				}
				i++;
			}
		}
		if (str[i] == '"' && escflags & 4)
		{
			i++;
			while (str[i] != '"')
			{
				if (str[i] == '\\' && escflags & 1)
				{
					if (str[i + 1] != 0)
						i++;
					i++;
					continue;
				}
				i++;
			}
		}
		j = 0;
		while (delim[j] != 0)
		{
			if (str[i] == delim[j])
				break;
			j++;
		}
		if (delim[j] != 0)
			break;
		i++;
	}
	saved_string = str;
	if (str[i] != 0)
	{
		saved_string = (saved_string + i + 1);
		str[i] = '\0';
	}
	else
	{
		saved_string = '\0';
	}
	return (str);
}

/**
 *_cd - change directory builtin
 * @av: argument to work with
 * Return: int
 */
int _cd(char *av[])
{
	char *oldpwd = NULL, *newpath, *pathbit, *newptr;
	char *homestr = "HOME", *oldpwdstr = "OLDPWD";
	int ret, printpath = 0;

	oldpwd = getcwd(oldpwd, 0);
	if (oldpwd == NULL)
		return (1);
	if (av[1] == NULL || av[1][0] == 0)
	{
		newpath = fetchenv(homestr);
		if (newpath == homestr)
			newpath = _strdup("");
		av[1] = newpath;
		av[2] = NULL;
	}
	else if (av[1][0] == '-' && av[1][1] == 0)
	{
		newpath = fetchenv(oldpwdstr);
		if (newpath == oldpwdstr)
			newpath = _strdup("");
		printpath = 1;
		free(av[1]);
		av[1] = newpath;
	}
	newpath = malloc(sizeof(char) * (_strlen(oldpwd) + _strlen(av[1]) + 2));
	if (newpath == NULL)
		return (-1);
	newptr = newpath;
	pathbit = oldpwd;
	if (av[1][0] != '/' && pathbit[1] != 0)
		while (*pathbit)
			*newptr++ = *pathbit++;
	*newptr++ = '/';
	pathbit = strtokenize(av[1], "/");
	while (pathbit != NULL)
	{
		if (pathbit[0] == '.' && pathbit[1] == '.'
		    && pathbit[2] == 0)
		{
			newptr--;
			if (newptr != newpath)
				newptr--;
			while (*newptr != '/')
				newptr--;
			*newptr++ = '/';
		}
		else if (!(pathbit[0] == '.' && pathbit[1] == 0))
		{
			while (*pathbit)
				*newptr++ = *pathbit++;
			*newptr++ = '/';
		}
		pathbit = strtokenize(NULL, "/");
	}
	if (newptr != newpath && newptr != newpath + 1)
		newptr--;
	*newptr = 0;
	ret = chdir(newpath);
	if (ret == 0)
	{
		_setenv("OLDPWD", oldpwd);
		free(oldpwd);
		_setenv("PWD", newpath);
		if (printpath)
			printfstr(1, newpath, "\n", NULL);
		free(newpath);
		return (0);
	}
	printerr(": cd: can't cd to ");
	printfstr(STDERR_FILENO, av[1], "\n", NULL);
	free(oldpwd);
	free(newpath);
	return (ret);
}


/**
 * exitcleanup - cleans up various vars before exiting
 * @av: argument list to free (if any)
 * Return: void
 */

void exitcleanup(char **av)
{
	PowerShell *sptr = *(fetchvariable()), *snext;
	alias *aptr = *(fetchall()), *anext;
	char **environ = *(fetchenviron());
	int i = 0;

	if (av != NULL)
		for (i = 0; av[i] != NULL; i++)
			free(av[i]);
	i = 0;
	while (environ[i] != NULL)
		free(environ[i++]);
	free(environ);
	while (sptr != NULL)
	{
		free(sptr->value);
		free(sptr->variable);
		sptr = sptr->dest;
	}
	free(*(fetchvariable()));
	sptr = *(fetchvalue());
	while (sptr != NULL)
	{
		free(sptr->value);
		free(sptr->variable);
		snext = sptr->dest;
		free(sptr);
		sptr = snext;
	}
	while (aptr != NULL)
	{
		free(aptr->value);
		free(aptr->name);
		anext = aptr->dest;
		free(aptr);
		aptr = anext;
	}
}
