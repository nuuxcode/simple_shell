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
	};
	size_t i;
	size_t nbuiltin = sizeof(builtin) / sizeof(builtin[0]);

	for (i = 0; i < nbuiltin; i++)
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
	free_array(d->av);
	free(d->cmd);
	exit(EXIT_FAILURE);
}

/**
 * builtin_env - prints the current environment
 * @d: data struct input
 * Return: void
 */
void builtin_env(void)
{
	char **env = environ;

	int i = 0;

	while (env[i])
	{
		_printf(env[i]);
		_printf("\n");
		i++;
	}
}
