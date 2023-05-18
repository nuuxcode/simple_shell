#include <unistd.h>	  /*write*/
#include <stdlib.h>	  /*exit*/
#include <stdio.h>	  /*stdin*/
#include <sys/wait.h> /*wait*/
#include <errno.h>

int main(int ac, char **av)
{
	char *cmd = NULL;
	size_t n = 0;
	ssize_t nread;
	pid_t child_pid = 0;
	int status = 0;
	const char prompt[] = "#nuux$ ";
	char *av[] = {cmd, NULL};
	(void)ac;

	while (1)
	{
		write(STDOUT_FILENO, prompt, sizeof(prompt));
		n = 0;
		nread = getline(&cmd, &n, stdin);
		/* check getline error and exit with error (also ctrl+d)*/
		if (nread == -1)
			exit(1);
		/*user input remplace the new line with end of line*/
		cmd[nread - 1] = '\0';
		if (access(cmd, F_OK) == -1)
			perror(av[0]);
		else
		{
			child_pid = fork();
			if (child_pid == 0 && execve(cmd, av, NULL) != 0)
				perror(av[0]);
		}
		wait(&status);
	}
	free(cmd);
	return (0);
}

/*
display prompt (always on after each command)
give user input
	get input (it end with\n) (simple command 1 word)
		check if it exist
			if not print error
			if it exist do a fork and execve
case to test :
	ctrl+d : exit
*/
