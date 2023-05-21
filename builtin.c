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
		{NULL, NULL},
	};
	int i = 0;

	for (i = 0; builtin[i].cmd; i++)
	{
		if (strcmp(d->av[0], builtin[i].cmd) == 0)
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
	if (d->av[1] && _isnumber(d->av[1]))
		d->last_exit_status = atoi(d->av[1]);
	free_array(d->av);
	free(d->cmd);
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
