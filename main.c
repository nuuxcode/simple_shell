#include <unistd.h>	  /*write*/
#include <stdlib.h>	  /*exit*/
#include <stdio.h>	  /*stdin*/
#include <sys/wait.h> /*wait*/
#include <errno.h>
#include <string.h> /*strlen*/

int main(int ac, char **argv)
{
	char *cmd = NULL;
	size_t n = 0;
	ssize_t nread;
	pid_t child_pid = 0;
	int status = 0;
	const char prompt[] = "#nuux$ ";
	char **av = NULL;
	(void)ac, (void)argv;
	char *token;
	char *delim = " ";
	int tokens_total = 0;
	int i = 0;

	while (1)
	{
		/*allocate memory for the command and argument array*/
		av = malloc(2 * sizeof(char *));
		av[0] = NULL;
		av[1] = NULL;
		write(STDOUT_FILENO, prompt, sizeof(prompt));
		n = 0;
		i = 0;
		tokens_total = 0;
		nread = getline(&cmd, &n, stdin);
		/* check getline error and exit with error (also ctrl+d)*/
		if (nread == -1)
		{
			free(cmd);
			free(av);
			/*perror("getline");*/
			exit(EXIT_FAILURE);
		}
		/*user input remplace the new line with end of line*/
		cmd[nread - 1] = '\0';
		/*make array of cmd and argument*/
		token = strtok(cmd, delim);
		while (token)
		{
			av = realloc(av, (tokens_total + 2) * sizeof(char *));
			if (av == NULL)
			{
				while (av[i])
				{
					/*printf("Realloc error:%d %s\n", tokens_total, av[i]);*/
					free(av[i]);
					i++;
				}
				free(av);
				free(cmd);
				perror("realloc");
				exit(EXIT_FAILURE);
			}
			av[tokens_total] = realloc(av[tokens_total], (strlen(token) + 1) * sizeof(char));
			strcpy(av[tokens_total], token);
			tokens_total++;
			token = strtok(NULL, delim);
		}
		av[tokens_total] = NULL;
		/*check if file exist before fork*/
		if (access(av[0], F_OK) == -1)
			perror("access");
		else
		{
			child_pid = fork();
			if (child_pid == 0 && execve(av[0], av, NULL) == -1)
				perror("execve");

			wait(&status);
		}
		i = 0;
		while (av[i])
		{
			/*printf("End of loop : %d %s\n", tokens_total, av[i]);*/
			free(av[i]);
			i++;
		}
		free(cmd);
		free(av);
	}
	return (0);
}
