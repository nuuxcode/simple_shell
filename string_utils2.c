#include "main.h"
/**
 * _strdup - returns a pointer to a newly allocated space in memory,
 * which contains a copy of the string given as a parameter.
 *
 * @str: string input
 *
 * Return: pointer
 */
char *_strdup(const char *str)
{
	int i, len = 0;
	char *result;

	if (str == NULL)
		return (NULL);

	while (str[len] != '\0')
		len++;

	result = (char *)malloc((len + 1) * sizeof(char));

	if (result == NULL)
		return (NULL);

	for (i = 0; i <= len; i++)
		result[i] = str[i];

	return (result);
}
