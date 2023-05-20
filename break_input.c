#include "shell.h"
/**
 * lexical_analysis - breaks a line of input into smaller units or tokens
 * @input: user input
 * Return: smaller units or tokens
 */
char **lexical_analysis(char *input)
{
	int index = 0, size;
	char **str = NULL;
	char *unit = NULL;

	for (size = 0; input[size] != '\0'; size++)
		;

	str = (char **)malloc(sizeof(char *) * size);
	unit = strtok(input, DELIM);
	str[index++] = unit;

	while (unit != NULL)
	{
		index++;
		unit = strtok(NULL, DELIM);
		str[index] = unit;
	}
	return (str);
}
