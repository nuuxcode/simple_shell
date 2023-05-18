#include <unistd.h>	  /*write*/
#include <stdlib.h>	  /*exit*/
#include <stdio.h>	  /*stdin*/
#include <sys/wait.h> /*wait*/
#include <errno.h>
#include <string.h> /*strlen*/
#include <signal.h>

typedef struct
{
	char **av;
	char *cmd;
	char *shell_name;
	int main_loop;
} data;
data global_data;
void free_av()
{
	int i = 0;
	if (!global_data.av)
		return;
	while (global_data.av[i])
	{
		/*printf("End of loop : %d %s\n", tokens_total, av[i]);*/
		free(global_data.av[i]);
		i++;
	}
	free(global_data.av);
	/*printf("freed av...\n");*/
}
void handler_sigint(int sig)
{
	if (global_data.cmd)
	{
		free(global_data.cmd);
		/*printf("free cmd...\n");*/
	}
	free_av();
	/*printf("Received SIGINT signal. Exiting...\n");*/
	exit(sig);
}
int main(int ac, char **argv)
{
	global_data.cmd = NULL;
	global_data.av = NULL;
	global_data.shell_name = argv[0];
	global_data.main_loop = 1;
	size_t n = 0;
	ssize_t nread;
	pid_t child_pid = 0;
	int status = 0, tokens_total = 0;
	const char prompt[] = "#csisfun$ ";
	(void)ac, (void)argv;
	char *token, *delim = " ";

	signal(SIGINT, handler_sigint);
	while (global_data.main_loop)
	{
		global_data.av = malloc(2 * sizeof(char *));
		global_data.av[0] = NULL;
		global_data.av[1] = NULL;
		write(STDOUT_FILENO, prompt, sizeof(prompt));
		n = 0;
		tokens_total = 0;
		nread = getline(&global_data.cmd, &n, stdin);
		/* check getline error and exit with error (also ctrl+d)*/
		if (nread == -1)
		{
			free(global_data.cmd);
			free(global_data.av);
			/*perror("getline");*/
			exit(EXIT_FAILURE);
		}
		/*user input remplace the new line with end of line*/
		global_data.cmd[nread - 1] = '\0';
		/*make array of cmd and argument*/
		token = strtok(global_data.cmd, delim);
		while (token)
		{
			global_data.av = realloc(global_data.av, (tokens_total + 2) * sizeof(char *));
			if (global_data.av == NULL)
			{
				free_av();
				free(global_data.cmd);
				perror(global_data.shell_name);
				exit(EXIT_FAILURE);
			}
			global_data.av[tokens_total] = realloc(global_data.av[tokens_total], (strlen(token) + 1) * sizeof(char));
			strcpy(global_data.av[tokens_total], token);
			tokens_total++;
			token = strtok(NULL, delim);
		}
		global_data.av[tokens_total] = NULL;
		/*check if file exist before fork*/
		if (access(global_data.av[0], F_OK) == -1)
			perror(global_data.shell_name);
		else
		{
			child_pid = fork();
			if (child_pid == 0 && execve(global_data.av[0], global_data.av, NULL) == -1)
				perror(global_data.shell_name);

			wait(&status);
		}
		free_av();
		free(global_data.cmd);
	}
	return (0);
}
