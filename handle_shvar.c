#include "shell.h"
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
	PowerShell *ptr = variable;

	while (ptr != NULL && _strcmp(ptr->variable, name))
	{
		ptr = ptr->dest;
	}
	if (ptr != NULL)
	{
		return (_strdup(ptr->value));
	}
	ptr = value;
	while (ptr != NULL && _strcmp(ptr->variable, name))
	{
		ptr = ptr->dest;
	}
	if (ptr == NULL)
	{
		return (name);
	}
	return (_strdup(ptr->value));
}
/**
 * setsvar - sets shell var
 * @name: name of var
 * @val: value of var
 * Return: int
 */
int setsvar(char *name, char *val)
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
		ptr = ptr->dest;
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
 * unsetsvar - unset shell var
 * @name: name of var to unset
 * Return: int
 */
int unsetsvar(char *name)
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
	while (ptr->dest != NULL && _strcmp(ptr->dest->variable, name))
		ptr = ptr->dest;
	if (!_strcmp(ptr->dest->variable, name))
	{
		next = ptr->dest->dest;
		free(ptr->dest->variable);
		free(ptr->dest->value);
		free(ptr->dest);
		ptr->dest = next;
	}
	return (0);
}
