#include "main.h"

void _fputs(const char *str)
{
	while (*str)
	{
		write(STDOUT_FILENO, str, 1);
		str++;
	}
}
void free_av(data *d)
{
	int i;
	if (!d->av)
		return;

	for (i = 0; d->av[i]; i++)
		free(d->av[i]);

	free(d->av);
}

void handler_sigint(int sig)
{
	const char prompt[] = "\n#csisfun$ ";
	(void)sig;
	_fputs(prompt);
}

void token_cmd(data *d, const char *delim)
{
	char *token;
	int tkn_ttl = 0;

	token = strtok(d->cmd, delim);
	while (token)
	{
		d->av = realloc(d->av, (tkn_ttl + 2) * sizeof(char *));
		if (d->av == NULL)
		{
			free_av(d);
			free(d->cmd);
			perror(d->shell_name);
			exit(EXIT_FAILURE);
		}
		d->av[tkn_ttl] = strdup(token);
		tkn_ttl++;
		token = strtok(NULL, delim);
	}

	d->av[tkn_ttl] = NULL;
}

void exec_cmd(data *d)
{
	pid_t child_pid = fork();
	int status = 0;

	if (child_pid == -1)
	{
		perror(d->shell_name);
		free_av(d);
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

void read_cmd(data *d)
{
	size_t n = 0;
	ssize_t nread;

	nread = getline(&d->cmd, &n, stdin);

	if (nread == -1)
	{
		free(d->cmd);
		free(d->av);
		exit(EXIT_FAILURE);
	}

	d->cmd[nread - 1] = '\0';
}

void init_data(data *d, const char *shell_name)
{
	d->cmd = NULL;
	d->av = NULL;
	d->shell_name = shell_name;
}

void run(data *d)
{
	const char prompt[] = "#csisfun$ ";

	signal(SIGINT, handler_sigint);

	while (1)
	{
		d->av = malloc(2 * sizeof(char *));
		d->av[0] = NULL;
		d->av[1] = NULL;

		_fputs(prompt);

		read_cmd(d);

		token_cmd(d, " ");

		if (access(d->av[0], F_OK) == -1)
			perror(d->shell_name);
		else
			exec_cmd(d);

		free_av(d);
		free(d->cmd);
	}
}

int main(int ac, char **argv)
{
	data d;

	(void)ac;
	init_data(&d, argv[0]);
	run(&d);

	return 0;
}
