#include "shell.h"
/**
 * getalist - static wrapper getalias list
 * Return: address alist
 *
 */
alias **fetchall()
{
	static alias *adr;

	return (&adr);
}

/**
 * fetchalias - fetches all alias value
 * @name: name of alias
 * Return: original argument if not found, otherwise value
 */
char *fetchalias(char *name)
{
	alias *all = *(fetchall());
	alias *ptr = all;

	while (ptr != NULL && _strcmp(ptr->name, name))
	{
		ptr = ptr->dest;
	}
	if (ptr == NULL)
	{
		return (name);
	}
	free(name);
	return (fetchalias(_strdup(ptr->value)));
}

/**
 * printalias - print alias and value
 * @name: name of alias
 * @val: value to set alias to
 * Return: 0 upon success
 */
int printalias(char *name, char *val)
{
	alias **alistroot = fetchall();
	alias *alist = *alistroot;
	alias *ptr = alist, *new;

	if (alist == NULL)
	{
		new = malloc(sizeof(alias));
		if (new == NULL)
			return (-1);
		new->name = name;
		new->value = val;
		new->dest = NULL;
		*alistroot = new;
		return (0);
	}
	while (_strcmp(ptr->name, name) && ptr->dest != NULL)
		ptr = ptr->dest;
	if (!_strcmp(ptr->name, name))
	{
		free(ptr->value);
		ptr->value = val;
		free(name);
	}
	else
	{
		new = malloc(sizeof(alias));
		if (new == NULL)
			return (-1);
		new->name = name;
		new->value = val;
		new->dest = NULL;
		ptr->dest = new;
	}
	return (0);
}
/**
 * unsetalias - unset alias of name variable
 * @name: name of the alias
 * Return: 0 if sucessful
 */
int unsetalias(char *name)
{
	alias *alist = *(fetchall());
	alias *ptr = alist, *next;

	if (alist == NULL)
		return (0);
	if (!(_strcmp(ptr->name, name)))
	{
		alist = alist->dest;
		free(ptr->value);
		free(ptr);
		return (0);
	}

	while (ptr->dest != NULL && _strcmp(ptr->dest->name, name))
		ptr = ptr->dest;
	if (!_strcmp(ptr->dest->name, name))
	{
		next = ptr->dest->dest;
		free(ptr->dest->name);
		free(ptr->dest);
		ptr->dest = next;
	}
	return (0);
}
/**
 * aliascmd - tokenizes arguments for alias command
 * @av: arguments
 * Return: 1
 */
int aliascmd(char *av[])
{
	alias *alist = *(fetchall());
	alias *ptr = alist;
	int i;
	char *name, *val;

	if (av[1] == NULL)
	{
		while (ptr != NULL)
		{
			fprintstrs(1, ptr->name, "='", ptr->value, "'\n", NULL);
			ptr = ptr->dest;
		}
		return (0);
	}
	for (i = 1; av[i] != NULL; i++)
	{
		name = strtok(av[i], "=");
		val = strtok(NULL, "=");
		if (val != NULL)
		{
			name = _strdup(name);
			if (name == NULL)
				return (-1);
			val = _strdup(val);
			if (val == NULL)
			{
				free(name);
				return (-1);
			}
			printalias(name, val);
		}
		else
		{
			val = _strdup(name);
			val = fetchalias(val);
			if (!_strcmp(val, name))
			{
				fprintstrs(1, "alias: ", name, " not found\n", NULL);
				free(val);
			}
			else
			{
				fprintstrs(1, name, "='", val, "'\n", NULL);
				free(val);
			}
		}
	}
	return (0);
}
