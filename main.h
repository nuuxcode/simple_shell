#ifndef MAIN_H
#define MAIN_H


#define PROMPT "#csisfun$ "

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

extern char **environ;
/**
 * struct data - holds the main data.
 * @av: Array of tokens to pass for execve
 * @cmd: The user input, the command line
 * @shell_name: The name of the shell program
 * @last_exit_status: last exit status of last command executed
 * @flag_setenv: 1 if user did exec setenv (use it to free memory)
 */
typedef struct data
{
	char **av;
	char *cmd;
	const char *shell_name;
	int last_exit_status;
	int flag_setenv;
} data;

/**
 * struct builtin - holds the main data.
 * @cmd: built in cmd
 * @f: function of builtin cmd
 */
typedef struct builtin
{
	const char *cmd;
	void (*f)(data *d);
} builtin;

/* builtin.c */
int exec_builtin(data *d);
void builtin_exit(data *d);
void builtin_env(data *d);
void builtin_setenv(data *d);
void builtin_unsetenv(data *d);

/* helpers.c */
void _printf(const char *str);
void free_array(char **array);
void split(data *d, const char *delim);
void init_data(data *d, const char *shell_name);
void read_cmd(data *d);

/* helpers2.c */
void _perror(const char *str1, const char *str2);

/* exec.c */
void start_process(data *d);
void handler_sigint(int sig);
void _exec(data *d);

/* string_utils.c*/
unsigned int _strlen(char *str);
void remove_left_spaces(char *str);
int _isdigit(int c);
int _isnumber(const char *status);

/* path.c*/
char *_getenv(char *name);
int _which(data *d);
int _setenv(data *d, char *name, char *value);

#endif
