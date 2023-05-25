#include "shell.h"

/**
 * shellstate - gets a list of the shell state
 * Return: address of the shell state
 */

ShellState **getshellstate()
{
	static ShellState *adr;

	return (&adr);
}

/**
 * setshellstate - set shellstate and value
 * @cmd: command entered
 * Return: 0 upon success
 */

int setshellstate(char *cmd)
{
	ShellState **root = getshellstate();
	ShellState *shs = *root;
	ShellState *ptr = shs, *new;

	if (shs == NULL)
	{
		new = malloc(sizeof(ShellState));
		if (new == NULL)
			return (-1);

		new->cmd = _strdup(cmd);
		new->dest = NULL;
		*root = new;
		return (0);
	}
	while (ptr->dest != NULL)
		ptr = ptr->dest;

	new = malloc(sizeof(ShellState));
	if (new == NULL)
		return (-1);
	new->cmd = _strdup(cmd);
	new->dest = NULL;
	ptr->dest = new;
	return (0);
}

/**
 * printshellstate - prints all elements of shellstate
 * Return: total number of elements
 */

int printshellstate(void)
{
	ShellState **root = getshellstate();
	ShellState *h = *root;
	int total, len, numlen;
	char *s, *num;

	total = 0;
	while (h != NULL)
	{
		len = _strlen(h->cmd);
		s = h->cmd;
		num = itos(total);
		numlen = _strlen(num);
		write(1, num, numlen);
		_putchar(' ');
		write(1, s, len);
		h = h->dest;
		total++;
	}
	return (total);
}

/**
 * exitshellstate - exit shellstate and send a copy to file
 * Return: a shell history file if successful, otherwise 1
 */

int exitshellstate(void)
{

	int fd, len;
	char *file = ".shell_history";
	char *s;

	ShellState **root = getshellstate();
	ShellState *shs = *root;
	ShellState *ptr = shs;

	fd = open(file, O_CREAT | O_RDWR, 0600);
	if (fd == -1)
		return (-1);

	while (shs != NULL)
	{
		ptr = shs->dest;
		s = shs->cmd;
		len = _strlen(s);
		write(fd, s, len);
		free(shs->cmd);
		free(shs);
		shs = ptr;
	}

	close(fd);
	return (1);
}
