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
				name = strtok(temp, " ");
				temp = strtok(NULL, "");
				ptr = temp;
				input = 1;
				name = strtok(name, "=");
				val = strtok(NULL, "");
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
 * cleanarg - cleans arguments and functional quotes
 * @arg: - argument to clean
 * Return: cleaned argument
 */
char *cleanarg(char *arg)
{
	char *newbuf, *ptr, *ptr2;
	size_t len = 0;
	int inquote = 0;

	ptr = arg;
	while (*ptr != 0)
	{
		if (*ptr == '\\' && !inquote)
		{
			ptr++;
			if (*ptr != 0)
			{
				len++;
				ptr++;
			}
			continue;
		}
		if (*ptr == '\\' && inquote == 2)
		{
			ptr++;
			if (*ptr == '$' || *ptr == '#' || *ptr == ';' || *ptr == '\\')
			{
				len++;
				ptr++;
			}
			else
				len++;
			continue;
		}
		if (!inquote && *ptr == '"')
		{
			inquote = 2;
			ptr++;
			continue;
		}
		if (!inquote && *ptr == '\'')
		{
			inquote = 1;
			ptr++;
			continue;
		}
		if ((inquote == 1 && *ptr == '\'') || (inquote == 2 && *ptr == '"'))
		{
			inquote = 0;
			ptr++;
			continue;
		}
		if (*ptr == 0)
			break;
		ptr++;
		len++;
	}
	newbuf = malloc(sizeof(char) * (len + 1));
	if (newbuf == NULL)
		return (NULL);
	ptr = arg;
	ptr2 = newbuf;
	inquote = 0;
	while (*ptr != 0)
	{
		if (*ptr == '\\' && !inquote)
		{
			ptr++;
			if (*ptr != 0)
				*ptr2++ = *ptr++;
			continue;
		}
		if (*ptr == '\\' && inquote == 2)
		{
			ptr++;
			if (*ptr == '$' || *ptr == '#' || *ptr == ';' || *ptr == '\\')
				*ptr2++ = *ptr++;
			else
				*ptr2++ = '\\';
			continue;
		}
		if (!inquote && *ptr == '"')
		{
			inquote = 2;
			ptr++;
			continue;
		}
		if (!inquote && *ptr == '\'')
		{
			inquote = 1;
			ptr++;
			continue;
		}
		if ((inquote == 1 && *ptr == '\'') || (inquote == 2 && *ptr == '"'))
		{
			inquote = 0;
			ptr++;
			continue;
		}
		if (*ptr != 0)
			*ptr2++ = *ptr++;
	}
	*ptr2 = 0;
	free(arg);
	return (newbuf);
}

/**
 * tildeexpand - handle expanding ~ where appropriate
 * @buf: buffer to process
 * Return: processed buffer
 */
char *tildeexpand(char *buf)
{
	char *tildeptr = buf, *endptr, *homepath, *newbuf, *bufptr, *newptr;
	int inquotes = 0;

	while (*tildeptr != 0)
	{
		tildeptr = buf;
		while (*tildeptr != '~' && *tildeptr != 0)
		{
			if (*tildeptr == '\\')
			{
				tildeptr++;
				if (*tildeptr != 0)
					tildeptr++;
				continue;
			}
			if (inquotes != 1 && *tildeptr == '"')
			{
				inquotes = 2;
				while (*tildeptr != '"' && *tildeptr != 0)
				{
					if (*tildeptr == '\\')
					{
						tildeptr++;
						inquotes = *tildeptr != 0 && tildeptr++;
						inquotes = 2;
						continue;
					}
					tildeptr++;
				}
			}
			if (*tildeptr == '\'' && inquotes != 2)
			{
				tildeptr++;
				while (*tildeptr != '\'' && *tildeptr != 0)
					tildeptr++;
			}
			tildeptr++;
		}
		if (*tildeptr == 0)
			return (buf);
		endptr = tildeptr;
		while (*endptr != '/' && *endptr != ' ' && *endptr != 0)
			endptr++;
		homepath = fetchenv("HOME");
		if (homepath == NULL)
			return (NULL);
		newbuf = malloc(_strlen(buf) - (size_t) endptr +
				(size_t) tildeptr + _strlen(homepath) + 1);
		if (newbuf == NULL)
		{
			free(homepath);
			return (NULL);
		}
		bufptr = buf;
		newptr = newbuf;
		while (bufptr < tildeptr)
			*newptr++ = *bufptr++;
		bufptr = homepath;
		while (*bufptr)
			*newptr++ = *bufptr++;
		while (*endptr)
			*newptr++ = *endptr++;
		*newptr = 0;
		free(homepath);
		free(buf);
		buf = newbuf;
	}
	return (newbuf);
}
/**
 * parseargs - parse arguments function
 * @buf: buffer pointer
 * Return: return value of command and frees buffer
 */
int parseargs(char **buf)
{
	char *av[1024], *ptr, *left, *right;
	int ac, ret = 0, newchk;

	if (*buf == NULL || **buf == 0)
		return (0);
	ptr = *buf;
	newchk = _strlen(*buf) - 1;
	if (ptr[newchk] == '\n')
		ptr[newchk] = 0;
	if (*buf[0] == 0)
	{
		free(*buf);
		return (0);
	}
	left = _strdup(strtokqe(*buf, ";", 7));
	right = _strdup(strtokqe(NULL, "", 7));
	free(*buf);
	*buf = left;
	if (right != NULL && *right != 0)
	{
		parseargs(&left);
		return (parseargs(&right));
	}
	left = strtokqe(*buf, "&", 7);
	right = strtokqe(NULL, "", 7);
	if (right != NULL && *right == '&')
	{
		left = _strdup(left);
		right = _strdup(right);
		free(*buf);
		*buf = left;
		ret = parseargs(&left);
		*buf = right;
		right++;
		right = _strdup(right);
		free(*buf);
		if (ret == 0)
			return (parseargs(&right));
		*buf = right;
		strtokqe(right, "|", 7);
		right = strtokqe(NULL, "", 7);
		if (right != NULL)
		{
			right++;
			right = _strdup(right);
			free(*buf);
			return (parseargs(&right));
		}
		free(*buf);
		return (ret);
	}
	else if (right != NULL)
	{
		*(right - 1) = '&';
	}
	left = strtokqe(*buf, "|", 7);
	right = strtokqe(NULL, "", 7);
	if (right != NULL && *right == '|')
	{
		left = _strdup(left);
		right = _strdup(right);
		free(*buf);
		*buf = left;
		ret = parseargs(&left);
		*buf = right;
		right++;
		right = _strdup(right);
		free(*buf);
		if (ret != 0)
			return (parseargs(&right));
		free(right);
		return (ret);
	}
	else if (right != NULL)
	{
		*(right - 1) = '|';
	}
	*buf = replacevars(buf);
	if (*buf == NULL)
		return (-1);
	*buf = tildeexpand(*buf);
	if (*buf == NULL)
		return (-1);
	*buf = processasgnvar(*buf);
	if (*buf == NULL)
		return (0);
	ac = 0;
	av[ac++] = _strdup(strtokqe(*buf, "\n ", 7));
	av[0] = fetchalias(av[0]);
	if (av[0] != NULL)
		av[0] = cleanarg(av[0]);
	while (av[ac - 1] != NULL)
	{
		av[ac] = _strdup(strtokqe(NULL, "\n ", 7));
		if (av[ac] != NULL)
			av[ac] = cleanarg(av[ac]);
		ac++;
	}
	ac--;
	av[ac] = NULL;
	free(*buf);
	*buf = NULL;
	ret = invokecmd(av);
	for (ac = 0; av[ac] != NULL; ac++)
		free(av[ac]);
	return (ret);
}
