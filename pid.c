#include "shell.h"
/**
 * _realloc - reallocates a memory block using malloc and free
 * @ptr: pointer to the previously allocated pointer
 * @old_size: size of previously allocated memory
 * @new_size: new size of the memory block
 * Return: resized memory block
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *input, *output;
	void *resized = 0;

	if (new_size == old_size)
	{
		return (ptr);
	}
	if (new_size > 0 || ptr == 0)
	{
		resized = malloc(new_size);
		if (resized == 0)
		{
			return (0);
		}
	}
	if (new_size > 0 && ptr != 0)
	{
		input = resized;
		output = ptr;
		if (new_size < old_size)
			old_size = new_size;
		while (old_size--)
		{
			*input++ = *output++;
		}
	}
	free(ptr);
	return (resized);
}

#include "shell.h"
/**
 * _getline - gets a line from fd or std input
 * @lineptr: buffer to fill line with
 * @fd: file descriptor
 * Return: num of characters
 */
int _getline(char **lineptr, int fd)
{
	int size = 1025, old_size = 0, r = 1, sum = 0;
	static char buffer[1025];
	static int begin, end;
	int c = 0, d;

	if (fd == -2)
	{
		begin = 0;
			end = 0;
	}
	if (lineptr == NULL)
		return (0);
	if (*lineptr == NULL)
	{
		*lineptr = malloc(sizeof(char) * size + 1);
		if (*lineptr == NULL)
			return (-1);
	}
	while (1)
	{
		if (begin == end)
		{
			while (sum < 1024 && r != 0)
			{
				r = read(fd, buffer + sum, 1024 - sum);
				begin = 0;
				sum += r;
				end = sum;
				for (d = 0; r != 0 && d < end; d++)
					if (buffer[d] == '\n')
						r = 0;
			}
			if (sum == 0)
			{
				buffer[0] = 0;
				return (sum);
			}
			buffer[sum] = 0;
			sum = 0;
		}
		for (; buffer[begin]; begin++)
		{
			if (begin == 1024)
				break;
			if (buffer[begin] == '\n')
			{
				(*lineptr)[c] = '\n';
				begin++;
				c++;
				(*lineptr)[c] = '\0';
				return (c);
			}
			else
			{
				(*lineptr)[c] = buffer[begin];
				c++;
			}
		}
		if (c + begin >= 1024)
		{
			old_size = size;
			size = size + 1024;
			*lineptr = _realloc(*lineptr, old_size, size);
			if (*lineptr == NULL)
				return (-1);
		}
		else
		{
			(*lineptr)[old_size + begin] = 0;
			return (c);
		}
	}
}

/**
 * getspecial - wrapper for getspecial static var
 * Return: address of shellvar special
 */

PowerShell **fetchvariable()
{
	static PowerShell *variable;

	return (&variable);
}

/**
 * getsvars - get static vars wrapper
 *
 * Return: address of var
 */
PowerShell **fetchvalue()
{
	static PowerShell *value;

	return (&value);
}

/**
 * _getpid - gets the pid of a currently running process
 * Return: string of the pid
 */
char *_getpid(void)
{
	char *s;
	char *pid;
	int fd;
	char *name;
	char *file = "/proc/self/status";

	s = malloc(256);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);

	while (_getline(&s, fd))
	{
		name = strtok(s, ":");
		if (!_strcmp(name, "Pid"))
		{
			pid = _strdup(strtok(NULL, "\n \t"));
			free(s);
			return (pid);
		}
		free(s);
		s = NULL;
	}
	return (NULL);
}
