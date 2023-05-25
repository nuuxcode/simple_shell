#include "main.h"

/**
 * exec_builtin - check if built in and then exec
 * @d: data struct input
 * Return: 1 if built in, 0 if not
 */
int exec_builtin(data *d)
{
	builtin builtin[] = {
		{"exit", builtin_exit},
		{"env", builtin_env},
		{"setenv", builtin_setenv},
		{"unsetenv", builtin_unsetenv},
		{"cd", builtin_cd},
		{NULL, NULL},
	};
	int i = 0;

	for (i = 0; builtin[i].cmd; i++)
	{
		if (_strcmp(d->av[0], builtin[i].cmd) == 0)
		{
			builtin[i].f(d);
			return (1);
		}
	}
	return (0);
}

/**
 * builtin_exit - exits the shell
 * @d: data struct input
 * Return: void
 */
void builtin_exit(data *d)
{
	const char *errorString = "./hsh: 1: exit: Illegal number: ";

	if (d->av[1])
	{
		if (d->av[1][0] != '-' && _isnumber(d->av[1]))
			d->last_exit_status = atoi(d->av[1]);
		else
		{
			write(STDERR_FILENO, errorString, strlen(errorString));
			write(STDERR_FILENO, d->av[1], strlen(d->av[1]));
			write(STDERR_FILENO, "\n", 1);
			d->last_exit_status = 2;
		}
	}
	free_array(d->av);
	free(d->cmd);
	if (d->flag_setenv)
		free_array(environ);
	exit(d->last_exit_status);
}

/**
 * builtin_env - prints the current environment
 * @d: data struct input
 * Return: void
 */
void builtin_env(data *d)
{
	int i = 0;

	(void)d;
	while (environ[i])
	{
		_printf(environ[i]);
		_printf("\n");
		i++;
	}
}
/**
 * builtin_setenv - Initialize a new environment variable,
 * or modify an existing one
 * @d: data struct input
 * Return: void
 */

void builtin_setenv(data *d)
{
	(void)d;
	if (d->av[1] && d->av[2])
	{
		if (_setenv(d, d->av[1], d->av[2]) == -1)
		{
			perror("setenv");
		}
	}
}

/**
 * builtin_unsetenv - Remove an environment variable
 * @d: data struct input
 * Return: void
 */
void builtin_unsetenv(data *d)
{
	int i, j;
	int len;

	(void)d;
	if (!d->av[1] || !getenv(d->av[1]))
	{
		_perror(d->shell_name, "variable not found.");
		return;
	}
	len = strlen(d->av[1]);
	for (i = 0; environ[i]; i++)
		if (strncmp(environ[i], d->av[1], len) == 0 && environ[i][len] == '=')
			for (j = i; environ[j]; j++)
				environ[j] = environ[j + 1];
}
