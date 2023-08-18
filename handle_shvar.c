#include "main.h"
/**
 * initializevars - function to initialize variables
 * @argc: arguemnts counter
 * Return: 0 if successful
 */
int initializevars(int argc, char **str)
{
	PowerShell **root = fetchvariable();
	PowerShell *special, *ptr;
	int input = 0;
	char nums[2] = {0, 0};

	*root = malloc(sizeof(PowerShell) * 15);
	if (*root == NULL)
	{
		return (-1);
	}
	special = *root;
	special->value = _strdup("0");
	special->variable = _strdup("?");
	ptr = special + 1;
	special->dest = ptr;
	for (input = 0; str[input] != NULL; input++)
	{
		nums[0] = input + '0';
		ptr->value = _strdup(str[input]);
		ptr->variable = _strdup(nums);
		ptr->dest = ptr + 1;
		ptr = ptr->dest;
	}
	while (input < 10)
	{
		nums[0] = input + '0';
		ptr->value = _strdup("0");
		ptr->variable = _strdup(nums);
		ptr->dest = ptr + 1;
		ptr = ptr->dest;
		input++;
	}
	ptr->variable = _strdup("$");
	ptr->value = _strdup("0");
	ptr->dest = ptr + 1;
	ptr = ptr->dest;
	ptr->variable = _strdup("#");
	ptr->value = itos(argc);
	ptr->dest = NULL;
	return (0);
}

/**
 * fetchvar - function that fetches shell variable
 * @name: variable name
 * Return: collected variable
 */
char *fetchvar(char *name)
{
	PowerShell *variable = *(fetchvariable()), *value = *(fetchvalue());
	PowerShell *ptr;

	for (ptr = variable; ptr != NULL; ptr = ptr->dest)
	{
		if (_strcmp(ptr->variable, name) == 0)
		{
			return (_strdup(ptr->value));
		}
	}
	for (ptr = value; ptr != NULL; ptr = ptr->dest)
	{
		if (_strcmp(ptr->variable, name) == 0)
		{
			return (_strdup(ptr->value));
		}
	}
	return (_strdup(name));
}

/**
 * asgnvar - assign the power shell variable
 * @name: variable name
 * @val: variable value
 * Return: 0 if successful
 */
int asgnvar(char *name, char *val)
{
	PowerShell **vars = fetchvalue();
	PowerShell *special = *(fetchvariable());
	PowerShell *ptr = special, *new;

	while (_strcmp(ptr->variable, name) && ptr->dest != NULL)
	{
		ptr = ptr->dest;
	}
	if (!_strcmp(ptr->variable, name))
	{
		free(ptr->value);
		ptr->value = _strdup(val);
		return (0);
	}
	ptr = *vars;
	if (ptr == NULL)
	{
		new = malloc(sizeof(PowerShell));
		if (new == NULL)
			return (-1);
		new->variable = _strdup(name);
		new->value = _strdup(val);
		new->dest = NULL;
		*vars = new;
		return (0);
	}
	while (_strcmp(ptr->variable, name) && ptr->dest != NULL)
	{
		ptr = ptr->dest;
	}
	if (ptr != NULL && !_strcmp(ptr->variable, name))
	{
		free(ptr->value);
		ptr->value = _strdup(val);
	}
	else
	{
		new = malloc(sizeof(PowerShell));
		if (new == NULL)
			return (-1);
		new->variable = _strdup(name);
		new->value = _strdup(val);
		new->dest = NULL;
		ptr->dest = new;
	}
	return (0);
}
/**
 * revokevar - revoke the power shell variable
 * @name: variable name to be revoked
 * Return: 0, if succesful
 */
int revokevar(char *name)
{
	PowerShell *vars = *fetchvalue();
	PowerShell *ptr = vars, *next;

	if (vars == NULL)
		return (0);
	if (!_strcmp(ptr->variable, name))
	{
		*vars = *vars->dest;
		free(ptr->variable);
		free(ptr->value);
		free(ptr);
		return (0);
	}
	for (; ptr->dest != NULL; ptr = ptr->dest)
	{
		if (!_strcmp(ptr->dest->variable, name))
		{
			next = ptr->dest->dest;
			free(ptr->dest->variable);
			free(ptr->dest->value);
			free(ptr->dest);
			ptr->dest = next;
			break;
	}
	}
	return (0);
}
