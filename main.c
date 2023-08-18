#include "main.h"
/**
 * main - main method that runs the shell
 * @argc: number of args
 * @argv: command line arguments
 * @environ: environment variiable
 * Return: result of entered command
 */
int main(int argc, char *argv[], char **environ)
{
	int result = 0;
	char *pid;

	initializevars(argc - 1, argv);
	pid = _getpid();
	asgnvar("$", pid);
	free(pid);
	_getline(NULL, -2);

	modallenv(environ, NULL);
	if (argc > 1)
		result = shellbatch(argv);
	else
		result = terminal();
	exitcleanup(NULL);
	exitshellstate();
	return (result);
}
