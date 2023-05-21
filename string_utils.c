#include "main.h"

/**
 * _strlen - return the nbr of char in str
 * @str: string input
 * Return: nbr of char in str.
 */

unsigned int _strlen(char *str)
{
	unsigned int i;

	for (i = 0; str[i] != '\0'; i++)
		;
	return (i);
}

/**
 * remove_left_spaces - remove leading spaces from a character string
 * @str: string input
 * Return: void.
 */

void remove_left_spaces(char *str)
{
	int i, j, len = _strlen(str);

	for (i = 0; i < len && str[i] == ' '; i++)
		;
	for (j = 0; i < len; i++, j++)
	{
		str[j] = str[i];
	}
	str[j] = '\0';
}

/**
 * _isdigit - check if charachter is number
 * @c: charachter
 * Return: 1 if its a digit 0 otherwise
 */
int _isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

/**
 * _isnumber - check if a string is a number
 * @status: string to be checked
 * Return: void
 */
int _isnumber(const char *status)
{
	if (status == NULL || status[0] == '\0')
		return (0);
	while (*status)
	{
		if (!_isdigit(*status))
			return (0);
		status++;
	}
	return (1);
}
