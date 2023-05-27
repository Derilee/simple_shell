#include "shell.h"
/**
 * scriptmode - shell script mode
 * @av: arguments
 * Return: 0 upon success or -1 if failure
 */
int scriptmode(char *av[])
{
	char *bufgl = NULL;
	int infile;
	ssize_t lenr = 0, eofflag = 0, ret = 0;

	infile = open(av[1], O_RDONLY);
	if (infile == -1)
	{
		printfstr(STDERR_FILENO, av[0], ": 0: Can't open ",
			   av[1], "\n", NULL);
		return (127);
	}
	while (!eofflag)
	{
		lenr = _getline(&bufgl, infile);
		if (lenr == 0 || lenr == -1)
		{
			free(bufgl);
			break;
		}
		if (bufgl[lenr - 1] != '\n')
			eofflag = 1;
		ret = inputchecker(&bufgl, STDIN_FILENO);
		bufgl = NULL;
		if (eofflag)
			break;
	}
	close(infile);
	return (ret);
}

/**
 * main - main method that runs the shell
 * @ac: number of args
 * @av: command line arg matrix
 * @environ: environment matrix
 * Return: return value of last command
 */
int main(int ac, char *av[], char **environ)
{
	int ret = 0;

	char *pidptr;

	initializevars(ac - 1, av);
	pidptr = _getpid();
	asgnvar("$", pidptr);
	free(pidptr);
	_getline(NULL, -2);

	modallenv(environ, NULL);
	if (ac > 1)
		ret = scriptmode(av);
	else
		ret = terminal();
	exitcleanup(NULL);
	exitshellstate();
	return (ret);
}
