#include "shell.h"
/**
 * fetchallenv - fucntion that fetches all environment variables
 * Return: an array of strings with the environ variables
 */
char **fetchallenv(void)
{
	char **environ = *(fetchenviron()), **var;
	size_t all = 0;

	var = environ;
	while (var[all] != NULL)
	{
		all++;
	}
	var = malloc(sizeof(char **) * (all + 1));
	if (var == NULL)
	{
		return (NULL);
	}
	while (all > 0)
	{
		var[all] = environ[all];
		all--;
	}
	var[all] = environ[all];
	return (var);
}

/**
 * modallenv - function that modify all environment to a new value
 * @env: environment variable
 * @val: value
 * Return: 0 if successful
 *        -1, if failure
 */
int modallenv(char **env, char *val)
{
	char ***environ = fetchenviron();
	size_t all = 0;

	while (env[all] != NULL)
		all++;
	if (val != NULL)
	{
		all++;
	}
	*environ = malloc(sizeof(char **) * (all + 1));
	if (*environ == NULL)
		return (-1);
	all = 0;
	while (env[all] != NULL)
	{
		if (val == NULL)
		{
			(*environ)[all] = _strdup(env[all]);
		}
		else
		{
			(*environ)[all] = env[all];
		}
		all++;
	}
	if (val != NULL)
	{
		(*environ)[all] = val;
		all++;
	}
	(*environ)[all] = NULL;
	if (val != NULL)
	{
		free(env);
	}
	return (0);
}
/**
 * _getenv - get local environment
 * @name: environment variable
 * Return: string of local environment
 */
char *_getenv(char *name)
{
	char **environ = *(fetchenviron());
	int i, j;
	char *s;

#ifdef DEBUGMODE
	printf("In getenv, name:%s\n", name);
#endif
	i = 0;
	while (environ[i] != NULL)
	{
		s = environ[i];
		j = 0;
#ifdef DEBUGSVARS
		printf("Checking against:%s\n", environ[i]);
#endif
		while (s[j] == name[j])
		{
			j++;
			if (name[j] == 0 && s[j] == '=')
				return (_strdup(s + j + 1));
		}
		i++;
	}
	return (name);
}
/**
 * _setenv - set environment for new value
 * @name: name of variable
 * @val: value of variable
 * Return: 0 or setallenv if success, -1 if fail
 */
int _setenv(char *name, char *val)
{
	char ***environroot = fetchenviron();
	char **environ = *environroot;
	int i, j, namel, vall;
	char *s, *ptr;

#ifdef DEBUGMODE
	printf("In setenv, name:%s:val:%s\n", name, val);
#endif
	if (name == NULL || val == NULL)
		return (0);
	namel = _strlen(name);
	vall = _strlen(val);
	ptr = malloc(sizeof(char) * (namel + vall + 2));
	if (ptr == NULL)
		return (-1);
	s = ptr;
	_strcpy(s, name);
	s += namel;
	_strcpy(s++, "=");
	_strcpy(s, val);
	s += vall;
	*s = 0;
#ifdef DEBUGMODE
	printf("Ptr mallocd:%s\n", ptr);
#endif
	i = 0;
	while (environ[i] != NULL)
	{
		s = environ[i];
		j = 0;
		while (s[j] == name[j])
		{
			j++;
			if (name[j] == 0 && s[j] == '=')
			{
				free(environ[i]);
				environ[i] = ptr;
				return (0);
			}
		}
		i++;
	}
	return (modallenv(*environroot, ptr));
}
/**
 * _unsetenv - unset environment
 * @name: name of variable to unset
 * Return: 0 if sucess
 *
 * testing functionality  copy environ, if hits skip over, realloc
 */
int _unsetenv(char *name)
{
	char **environ = *fetchenviron();
	int i, j;
	int check = 0;
	char *s;
	char **env;

#ifdef DEBUGMODE
	printf("In unsetenv, name:%s\n", name);
#endif
	if (name == NULL)
		return (0);

	i = 0;
	while (environ[i] != NULL)
	{
		s = environ[i];
		j = 0;
		while (s[j] == name[j])
		{
			j++;
			if (s[j] == '=' && name[j] == '\0')
			{
				check = 1;
				break;
			}
		}
		if (check == 1)
			break;
		i++;
	}
	free(environ[i]);
	while (environ[i] != NULL)
	{
		environ[i] = environ[i + 1];
		i++;
	}
	environ[i] = NULL;
	env = environ;
	modallenv(env, NULL);
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
	return (0);
}
