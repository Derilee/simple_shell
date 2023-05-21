#include "shell.h"
/**
 *
 */
int comp_Arg(char **Arg_str, int ct_output)
{
	int cal_path = 0;
	struct stat st;
	char *copy_Arg = NULL;

	copy_Arg = malloc(sizeof(char *) * _strlen(Arg_str[0]));
	copy_Arg = _strcpy(copy_Arg, Arg_str[0]);

	if (stat(Arg_str[0], &st) == 0 && copy_Arg[0] != '/')
		Arg_str[0] = check_path(Arg_str);

	else if (stat(Arg_str[0], &st) == -1)
		Arg_str[0] = check_path(Arg_str);

	if (_strcmp(copy_Arg, Arg_str[0]) != 0)
		cal_path = 1;

	if (stat(Arg_str[0], &st) == 0)
		ct_output = _fork(Arg_str, ct_output);

	else
	{
		handle_error(Arg_str[0]);
		ct_output = 127;
	}

	if (cal_path == 1)
		free(Arg_str[0]);

	free(copy_Arg);

	return (ct_output);
}


#include "shell.h"

/**
 * get_env - Get path.
 *
 * Return: PATH.
 */

char *get_env(void)
{
	int i;
	char **env = NULL, *Oper = NULL;
	extern char** environ;

	env = environ;

	for (i = 0; env[i] != NULL; i++)
	{
		if (_strncmp("PATH", env[i], 4) == 0)
			Oper = env[i];
	}

	if (Oper != NULL)
	{
		while (*Oper != '=')
			Oper++;

		Oper++;
	}

	return (Oper);
}

#include "shell.h"

/**
 * _fork - Create a child process
 *
 * @Arg_str: argument string
 * @ct_output: output.
 *
 * Return: output.
 */

int _fork(char **Arg_str, int ct_output)
{
	pid_t pid;
	int sts;

	pid = fork();

	if (pid == 0)
	{
		if (execve(Arg_str[0], Arg_str, NULL) == -1)
			perror("Error: execve");
	}

	else if (pid == -1)
		perror("Error: Fork failure");

	else
	{
		wait(&sts);

		if (WIFEXITED(sts))
			ct_output = WEXITSTATUS(sts);
	}

	return (ct_output);
}


#include "shell.h"

/**
 * check_path - Check_path.
 *
 * @Arg_str: argument string.
 *
 * Return: CP_arg
 *
 */

char *check_path(char **Arg_str)
{
	char *CP_PATH = NULL, *path = NULL;
	char *env = NULL, *CP_Arg = NULL, *len_env = NULL;
	size_t size_CP_Arg, size;
	struct stat st;

	env = get_env();

	if (env != NULL)
	{
		CP_Arg = Arg_str[0];

		size_CP_Arg = _strlen(CP_Arg);
		len_env = malloc(sizeof(char) * _strlen(env) + 1);
		len_env = _strcpy(len_env, env);
		path = strtok(len_env, ":");

		while (path != NULL)
		{
			size = _strlen(path) + size_CP_Arg + 2;
			CP_PATH = malloc(sizeof(char) * size);

			CP_PATH = _strcpy(CP_PATH, path);
			CP_PATH = _strcat(CP_PATH, "/");
			CP_PATH = _strcat(CP_PATH, CP_Arg);

			if (stat(CP_PATH, &st) == 0 && st.st_mode & X_OK)
			{
				free(len_env);
				return (CP_PATH);
			}

			path = strtok(NULL, ":");
			free(CP_PATH);
		}
		free(len_env);
	}
	return (CP_Arg);
}
