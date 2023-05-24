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
	{
		return (0);
	}
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
			{
				break;
			}
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
			}
			c++;
		}
		if (c + begin >= 1024)
		{
			old_size = size;
			size = size + 1024;
			*lineptr = _realloc(*lineptr, old_size, size);
			if (*lineptr == NULL)
			{
				return (-1);
			}
		}
		else
		{
			(*lineptr)[old_size + begin] = 0;
			return (c);
		}
	}
}
