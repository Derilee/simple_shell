#include "shell.h"

char ***fetchenviron();
PowerShell **fetchvariable();
PowerShell **fetchvalue();
alias **fetchall();

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
