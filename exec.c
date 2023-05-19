#include "main.h"

/**
 * start_process - start a new process
 * @d: data struct input
 * Return: void
 */

void start_process(data *d)
{
	pid_t child_pid = fork();
	int status = 0;

	if (child_pid == -1)
	{
		perror(d->shell_name);
		free_array(d->av);
		free(d->cmd);
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		if (execvp(d->av[0], d->av) == -1)
		{
			perror(d->shell_name);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}
}


/**
 * handler_sigint - Signal handler function
 * @signal: int input
 * Return: void
 */

void handler_sigint(int signal)
{
	const char prompt[] = "\n#csisfun$ ";
	(void)signal;
	_printf(prompt);
}

/**
 * _exec - exectute cmd
 * @d: data struct input
 * Return: void
 */

void _exec(data *d)
{
	const char prompt[] = "#csisfun$ ";

	signal(SIGINT, handler_sigint);

	while (1)
	{
		d->av = malloc(2 * sizeof(char *));
		d->av[0] = NULL;
		d->av[1] = NULL;

		_printf(prompt);

		read_cmd(d);

		split(d, " ");

		if (access(d->av[0], F_OK) == -1)
			perror(d->shell_name);
		else
			start_process(d);

		free_array(d->av);
		free(d->cmd);
	}
}