#include "main.h"

void free_av(data *d)
{
	int i = 0;

	if (!d->av)
		return;
	while (d->av[i])
	{
		free(d->av[i]);
		i++;
	}
	free(d->av);
}

void handler_sigint(int sig)
{
	const char prompt[] = "\n#csisfun$ ";
	(void)sig;
	write(STDOUT_FILENO, prompt, sizeof(prompt));
}

int main(int ac, char **argv)
{
	data d;

	d.cmd = NULL;
	d.av = NULL;
	d.shell_name = argv[0];
	size_t n = 0;
	ssize_t nread;
	pid_t child_pid = 0;
	int status = 0, tkn_ttl = 0;
	const char prompt[] = "#csisfun$ ";
	(void)ac, (void)argv;
	char *token, *delim = " ";

	signal(SIGINT, handler_sigint);

	while (1)
	{
		d.av = malloc(2 * sizeof(char *));
		d.av[0] = NULL;
		d.av[1] = NULL;
		write(STDOUT_FILENO, prompt, sizeof(prompt));
		n = 0;
		tkn_ttl = 0;
		nread = getline(&d.cmd, &n, stdin);

		if (nread == -1)
		{
			free(d.cmd);
			free(d.av);
			exit(EXIT_FAILURE);
		}

		d.cmd[nread - 1] = '\0';

		token = strtok(d.cmd, delim);
		while (token)
		{
			d.av = realloc(d.av, (tkn_ttl + 2) * sizeof(char *));
			if (d.av == NULL)
			{
				free_av(&d);
				free(d.cmd);
				perror(d.shell_name);
				exit(EXIT_FAILURE);
			}
			d.av[tkn_ttl] = realloc(d.av[tkn_ttl], (strlen(token) + 1) * sizeof(char));
			strcpy(d.av[tkn_ttl], token);
			tkn_ttl++;
			token = strtok(NULL, delim);
		}

		d.av[tkn_ttl] = NULL;

		if (access(d.av[0], F_OK) == -1)
			perror(d.shell_name);
		else
		{
			child_pid = fork();
			if (child_pid == 0 && execve(d.av[0], d.av, NULL) == -1)
				perror(d.shell_name);

			wait(&status);
		}

		free_av(&d);
		free(d.cmd);
	}

	return (0);
}
