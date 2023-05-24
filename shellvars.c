#include "shell.h"
/**
 * initsvars - initialize vars
 * @ac: arguemnts intiger
 * @av: string arguments
 * Return: int
 */
int initsvars(int ac, char **av)
{
	PowerShell **specialroot = fetchvariable();
	PowerShell *special;
	PowerShell *ptr;
	int i = 0;
	char nums[2] = {0, 0};

	*specialroot = malloc(sizeof(PowerShell) * 15);
	if (*specialroot == NULL)
		return (-1);
	special = *specialroot;
	special->value = _strdup("0");
	special->variable = _strdup("?");
	ptr = special + 1;
	special->dest = ptr;
	while (av[i] != NULL)
	{
		nums[0] = i + '0';
		ptr->value = _strdup(av[i]);
		ptr->variable = _strdup(nums);
		ptr->dest = ptr + 1;
		ptr = ptr->dest;
		i++;
	}
	while (i < 10)
	{
		nums[0] = i + '0';
		ptr->value = _strdup("0");
		ptr->variable = _strdup(nums);
		ptr->dest = ptr + 1;
		ptr = ptr->dest;
		i++;
	}
	ptr->variable = _strdup("$");
	ptr->value = _strdup("0");
	ptr->dest = ptr + 1;
	ptr = ptr->dest;
	ptr->variable = _strdup("#");
	ptr->value = itos(ac);
	ptr->dest = NULL;
	return (0);
}
/**
 * getsvar - gets shell variable
 * @name: name of shell var
 *
 * Return: original argument if not found
 */
char *getsvar(char *name)
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
