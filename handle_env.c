#include "shell.h"
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
 * fetchenv - fetch local environment and return the details
 * @details: environment variable
 * Return: details of local environment
 */
char *fetchenv(char *details)
{
	char **environ = *(fetchenviron());
	int input, var;
	char *str;

	for (input = 0; environ[input] != NULL; input++)
	{
		str = environ[input];
		var = 0;
		while (str[var] == details[var])
		{
			var++;
			if (details[var] == 0 && str[var] == '=')
			{
				return (_strdup(str + var + 1));
			}
		}
	}
	return (details);
}
/**
 * _setenv - function to implement the setenv builtin command
 * @variable: variable name
 * @value: value of the variable
 * Return: implemented setenv, if successful
 *          -1 if failure
 */
int _setenv(char *variable, char *value)
{
	char ***newenviron = fetchenviron();
	char **environ = *newenviron;
	int input, index, name, var;
	char *str, *ptr;

	if (variable == NULL || value == NULL)
		return (0);
	name = _strlen(variable);
	var = _strlen(value);
	ptr = malloc(sizeof(char) * (name + var + 2));
	if (ptr == NULL)
		return (-1);
	str = ptr;
	_strcpy(str, variable);
	str += name;
	_strcpy(str++, "=");
	_strcpy(str, value);
	str += var;
	*str = 0;
	for (input = 0; environ[input] != NULL; input++)
	{
		str = environ[input];
		for (index = 0; str[index] == variable[index]; index++)
		{
		if (variable[index] == 0 && str[index] == '=')
		{
			free(environ[input]);
			environ[input] = ptr;
			return (0);
		}
		}
	}
	return (modallenv(*newenviron, ptr));
}
/**
 * _unsetenv - function to implement the unsetenv builtin command
 * @variable: variable name to unset
 * Return: 0 if sucess
 */
int _unsetenv(char *variable)
{
	char **environ = *fetchenviron();
	int input, index, name = 0;
	char *str, **env;

	if (variable == NULL)
		return (0);
	for (input = 0; environ[input] != NULL; input++)
	{
		str = environ[input];
		for (index = 0; str[index] == variable[index]; index++)
		{
			if (str[index] == '=' && variable[index] == '\0')
			{
				name = 1;
				break;
			}
		}
		if (name == 1)
			break;
	}
	free(environ[input]);
	for (; environ[input] != NULL; input++)
	{
		environ[input] = environ[input + 1];
	}
	environ[input] = NULL;
	env = environ;
	modallenv(env, NULL);
	input = 0;
	while (env[input])
	{
		free(env[input]);
		input++;
	}
	free(env);
	return (0);
}
