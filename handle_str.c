#include "main.h"
/**
 * _strlen - function to calculate the length of a string
 * @str: the string to be counted
 * Return: the length of the string
 */
size_t _strlen(char *str)
{
	size_t len = 0;

	for (; *str != '\0'; str++)
	{
		len++;
	}
	return (len);
}

/**
* _strcat - function that concatenates two strings
* @dest: concat value to
* @src: caoncat value from
* Return: concatenated string
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
* Return: copied string
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
 * _strcmp - function to compare two strings
 * @s1: input value
 * @s2: input value
 * Return: str1 - str2, or 0 if they are the same
 */
int _strcmp(char *s1, char *s2)
{
    int index;

    if (s1 == NULL && s2 == NULL)
        return (0);
    if (s1 == NULL)
        return (-1);
    if (s2 == NULL)
        return (1);

    index = 0;
    while (s1[index] != '\0' || s2[index] != '\0')
    {
        if (s1[index] != s2[index])
        {
            return (s1[index] - s2[index]);
        }
        index++;
    }

    return (0);
}

/**
 * _strdup - function to duplicate two strings
 * @str: string value
 * Return: duplicated string
 */
char *_strdup(char *str)
{
	char *new_str;

	if (str == NULL)
	{
		return (NULL);
	}
	new_str = malloc(sizeof(char) * (_strlen(str) + 1));
	if (new_str == NULL)
	{
		return (NULL);
	}
	_strcpy(new_str, str);
	return (new_str);
}
