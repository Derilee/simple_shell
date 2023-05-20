#include "shell.h"
/**
 * handle_error - function that handle errors.
 * @cmd_line: command line
 */
void handle_error(char *cmd_line)
{
	int index = _strlen(cmd_line);

	write(STDERR_FILENO, cmd_line, index);
	write(STDERR_FILENO, ": not found\n", 12);
}
