#include "shell.h"
/**
 * _strlen - function to calculate the length of a string
 * @str: the string to be counted
 * Return: the length of the string
 */
int _strlen(char *str)
{
	int len = 0;

	for (; *str != '\0'; str++)
	{
		len++;
	}
	return (len);
}

/**
* _strcat - function that concatenates two strings
* @dest: input value
* @src: input value
* Return: void
*/
char *_strcat(char *dest, char *src)
{
	int i;
	int j;

	i = 0;
	while (dest[i] != '\0')
	{
		i++;
	}
	j = 0;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	dest[i] = '\0';
	return (dest);
}

/**
* _strcpy - function that copies the string pointed to by src
* @dest: copy to
* @src: copy from
* Return: string
*/

char *_strcpy(char *dest, char *src)
{
	int str = 0;
	int index = 0;

	while (*(src + str) != '\0')
	{
		str++;
	}
	for ( ; index < str ; index++)
	{
		dest[index] = src[index];
	}
	dest[str] = '\0';
	return (dest);
}

/**
* _strcmp - function to compare string values
* @s1: input value
* @s2: input value
* Return: s1[i] - s2[i]
*/

int _strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	return (0);
}

/**
 * _strncmp - function to compare string values
 * @s1: input value
 * @s2: input value
 * @n: input value
 * Return: 0, on sucess. -1, on failure
 */
int _strncmp(char *s1, char *s2, int n)
{
	while (*s1 && *s2 && n >= 0)
	{
		if (*s1 != *s2)
		{
			return (-1);
		}
		s1++;
		s2++;
		n--;
	}
	return (0);
}
