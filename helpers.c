#include "main.h"

/**
 * _printf - print a string to stander out put
 * @str: string input
 * Return: void
 */
void _printf(const char *str)
{
	while (*str)
	{
		write(STDOUT_FILENO, str, 1);
		str++;
	}
}

/**
 * free_array - free an array of pointers
 * @array: array of pointers
 * Return: void
 */

void free_array(char **array)
{
	int i;

	if (!array)
		return;

	for (i = 0; array[i]; i++)
		free(array[i]);

	free(array);
}

/**
 * split - split a given string by a delimiter
 * @d: data struct input
 * @delim: string input
 * Return: void
 */

void split(data *d, const char *delim)
{
	char *token;
	int ntoken = 0;

	d->av = malloc(2 * sizeof(char *));
	if (d->av == NULL)
	{
		free(d->cmd);
		perror(d->shell_name);
		exit(EXIT_FAILURE);
	}
	d->av[0] = NULL;
	d->av[1] = NULL;

	token = strtok(d->cmd, delim);
	while (token)
	{
		d->av = realloc(d->av, (ntoken + 2) * sizeof(char *));
		if (d->av == NULL)
		{
			free_array(d->av);
			free(d->cmd);
			perror(d->shell_name);
			exit(EXIT_FAILURE);
		}
		d->av[ntoken] = strdup(token);
		if (d->av[ntoken] == NULL)
		{
			free_array(d->av);
			free(d->cmd);
			perror(d->shell_name);
			exit(EXIT_FAILURE);
		}
		ntoken++;
		token = strtok(NULL, delim);
	}
	d->av[ntoken] = NULL;
}

/**
 * init_data - init data
 * @d: data struct input
 * @shell_name: string input
 * Return: void
 */

void init_data(data *d, const char *shell_name)
{
	d->cmd = NULL;
	d->av = NULL;
	d->shell_name = shell_name;
}

/**
 * read_cmd - get the commend from the prompt and structure it into data struct
 * @d: data struct input
 * Return: void
 */

void read_cmd(data *d)
{
	size_t n = 0;
	ssize_t nread;

	nread = getline(&d->cmd, &n, stdin);

	if (nread == -1)
	{
		free(d->cmd);
		exit(EXIT_FAILURE);
	}

	d->cmd[nread - 1] = '\0';
}
