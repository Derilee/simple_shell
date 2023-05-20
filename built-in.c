#include "shell.h"
/**
 * check_built-in
 *
int check_built-in(char **str, int ct_output, char *row)
{
	char *built_box[] = {"exit", "env"};

	if (!str || !*str)
		return 1;
	else if (!_strcmp(str[0], built_box[0]) || !_strcmp(str[0], built_box[1]))
		return built_in(str, ct_output, row);
	else
		return comp_Arg(str, ct_output);
}
*/
