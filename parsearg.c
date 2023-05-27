#include "shell.h"
/**
 * processasgnvar - process assigned powershell variables
 * @temp: temporary storage to store assigned variable
 * Return: processed new string if succesful
 *         or, NULL on failure
 */
char *processasgnvar(char *temp)
{
	int input;
	char *name, *val, *ptr, *newstr;
	char *tmpstg = temp;

	do {
		input = 0;
		ptr = temp;
		while (*ptr != '\0')
		{
			if (*ptr == '=')
			{
				name = strtokenize(temp, " ");
				temp = strtokenize(NULL, "");
				ptr = temp;
				input = 1;
				name = strtokenize(name, "=");
				val = strtokenize(NULL, "");
				asgnvar(name, val);
				if (temp == NULL)
				{
					free(tmpstg);
					return (NULL);
				}
				continue;
			}
			if (*ptr == ' ' || *ptr == 0)
			{
				temp = _strdup(temp);
				free(tmpstg);
				return (temp);
			}
			if (ptr == NULL)
			{
				free(tmpstg);
				return (NULL);
			}
			ptr++;
		}
	} while (input && *ptr != '\0');
	newstr = malloc(sizeof(char) * (_strlen(temp) + 1));
	if (newstr == NULL)
		return (NULL);
	newstr = _strcpy(newstr, temp);
	free(tmpstg);
	return (newstr);
}

/**
 * replacevar - function that replaces shell variable
 * @temp: temporary storage to store assigned variable
 * Return: processed new string if succesful
 */
char *replacevars(char **temp)
{
	char *var = *temp, *name, *val;
	size_t len = _strlen(*temp);
	size_t str;
	char *ptr = *temp, *src;

	while (*var != 0)
	{
		while (*var != '$' && *var != 0)
		{
			var++;
		}
		if (*var == 0)
			return (*temp);
		var++;

		str = 0;
		while (var[str] != 0 && var[str] != ' ' &&
			var[str] != '\n' && var[str] != '\\')
		{
			str++;
		}
		name = malloc(str + 1);
		if (name == NULL)
		{
			return (NULL);
		}
		_strncpy(name, var, str);
		name[str] = '\0';
		val = fetchenv(name);

		if (val == name)
		{
			val = fetchvar(name);
			if (val == name)
				val = _strdup("");
		}
		free(name);
		len = len - str + _strlen(val) + 1;
		name = malloc(len);
		while (*ptr != 0)
		{
			if (val != NULL && ptr == var)
			{
				while (*val != 0)
				{
					*src++ = *val++;
				}
				free(val);
				val = NULL;
				var = src;
				ptr += str + 1;
				if (*ptr == 0)
					break;
			}
			*src++ = *ptr++;
		}
		*src = *ptr;
		free(*temp);
		*temp = name;
	}
	return (*temp);
}

/**
 * filterarg - function that filters argument
 * @argc: - argument to filer
 * Return: filtered argument on success
 */
char *filterarg(char *argc)
{
	char *newstr, *ptr, *strptr;
	int input = 0;
	size_t len = 0;

	for (ptr = argc; *ptr; ptr++)
	{
		if (*ptr == '\\' && !input)
		{
			ptr++;
			if (*ptr)
			{
				len++;
			}
			continue;
		}
		if (*ptr == '\\' && input == 2)
		{
			ptr++;
			if (*ptr == '$' || *ptr == '#' || *ptr == ';' || *ptr == '\\')
			{
				len++;
			}
			else
				len++;
			continue;
		}
		if (!input && *ptr == '"')
		{
			input = 2;
			continue;
		}
		if (!input && *ptr == '\'')
		{
			input = 1;
			continue;
		}
		if ((input == 1 && *ptr == '\'') || (input == 2 && *ptr == '"'))
		{
			input = 0;
			continue;
		}
		len++;
	}
	newstr = malloc(len + 1);
	if (!newstr)
		return (NULL);

	strptr = newstr;
	input = 0;
	for (ptr = argc; *ptr; ptr++)
	{
		if (*ptr == '\\' && !input)
		{
			ptr++;
			if (*ptr)
				*strptr++ = *ptr;
			continue;
		}
		if (*ptr == '\\' && input == 2)
		{
			ptr++;
			if (*ptr == '$' || *ptr == '#' || *ptr == ';' || *ptr == '\\')
				*strptr++ = *ptr;
			else
				*strptr++ = '\\';
			continue;
		}
		if (!input && *ptr == '"')
		{
			input = 2;
			continue;
		}
		if (!input && *ptr == '\'')
		{
			input = 1;
			continue;
		}
		if ((input == 1 && *ptr == '\'') || (input == 2 && *ptr == '"'))
		{
			input = 0;
			continue;
		}
			*strptr++ = *ptr;
	}
	*strptr = '\0';
	free(argc);
	return (newstr);
}

/**
 * handlxpand - handle expanding ~ where appropriate
 * @buf: buffer to process
 * Return: processed buffer
 */
char *handlxpand(char *temp)
{
	char *ptr = temp, *strend, *home;
	char *newstr, *bufptr, *newptr;
	int input = 0;

	while (*ptr)
	{
		ptr = temp;
		while (*ptr && *ptr != '~')
		{
			if (*ptr == '\\')
			{
				ptr += 2;
				continue;
			}
			if (input != 1 && *ptr == '"')
			{
				input = 2;
				while (*ptr && *ptr != '"')
				{
					if (*ptr == '\\')
					{
						ptr += 2;
						continue;
					}
					ptr++;
				}
			}
			if (*ptr == '\'' && input != 2)
			{
				ptr++;
				while (*ptr && *ptr != '\'')
					ptr++;
			}
			ptr++;
		}
		if (!*ptr)
			return (temp);
		strend = ptr;
		while (*strend && *strend != '/' && *strend != ' ')
			strend++;
		home = fetchenv("HOME");
		if (!home)
			return (NULL);
		newstr = malloc(_strlen(temp) - (size_t)(strend - ptr)
				+ _strlen(home) + 1);
		if (!newstr)
		{
			free(home);
			return (NULL);
		}
		bufptr = temp;
		newptr = newstr;
		while (bufptr < ptr)
			*newptr++ = *bufptr++;
		bufptr = home;
		while (*bufptr)
			*newptr++ = *bufptr++;
		while (*strend)
			*newptr++ = *strend++;
		*newptr = '\0';
		free(home);
		free(temp);
		temp = newstr;
	}
	return (newstr);
}

/**
 * transargs - translates arguments function
 * @temp: temporary storage
 * Return: translated string
 */
int transargs(char **temp)
{
	char *argv[1024], *ptr, *input, *output;
	int argc, str = 0, newstr;

	if (!(*temp) || !(*temp)[0])
	return (0);
	ptr = *temp;
	newstr = _strlen(*temp) - 1;

	if (ptr[newstr] == '\n')
		ptr[newstr] = 0;

	if ((*temp)[0] == 0)
	{
		free(*temp);
		return (0);
	}

	input = _strdup(strtokqe(*temp, ";", 7));
	output = _strdup(strtokqe(NULL, "", 7));
	free(*temp);
	*temp = input;

	if (output && *output)
	{
		transargs(&input);
		return (transargs(&output));
	}

	input = strtokqe(*temp, "&", 7);
	output = strtokqe(NULL, "", 7);

	if (output && *output == '&')
	{
		input = _strdup(input);
		output = _strdup(output);
		free(*temp);
		*temp = input;
		str = transargs(&input);
		*temp = output;
		output++;
		output = _strdup(output);
		free(*temp);

		if (str == 0)
			return (transargs(&output));

		*temp = output;
		strtokqe(output, "|", 7);
		output = strtokqe(NULL, "", 7);

		if (output)
		{
			output++;
			output = _strdup(output);
			free(*temp);
			return (transargs(&output));
		}

		free(*temp);
		return (str);
	}
	else if (output)
	{
		*(output - 1) = '&';
	}

	input = strtokqe(*temp, "|", 7);
	output = strtokqe(NULL, "", 7);

	if (output && *output == '|')
	{
		input = _strdup(input);
		output = _strdup(output);
		free(*temp);
		*temp = input;
		str = transargs(&input);
		*temp = output;
		output++;
		output = _strdup(output);
		free(*temp);

		if (str != 0)
			return (transargs(&output));

		free(output);
		return (str);
	}
	else if (output)
	{
		*(output - 1) = '|';
	}

	*temp = replacevars(temp);
	if (!(*temp))
		return (-1);

	*temp = handlxpand(*temp);
	if (!(*temp))
		return (-1);

	*temp = processasgnvar(*temp);
	if (!(*temp))
		return (0);

	argc = 0;
	argv[argc++] = _strdup(strtokqe(*temp, "\n ", 7));
	argv[0] = fetchalias(argv[0]);

	if (argv[0])
		argv[0] = filterarg(argv[0]);

	while (argv[argc - 1])
	{
		argv[argc] = _strdup(strtokqe(NULL, "\n ", 7));
		if (argv[argc])
			argv[argc] = filterarg(argv[argc]);
		argc++;
	}

	argc--;
	argv[argc] = NULL;
	free(*temp);
	*temp = NULL;
	str = invokecmd(argv);

	for (argc = 0; argv[argc]; argc++)
		free(argv[argc]);

	return (str);
}
