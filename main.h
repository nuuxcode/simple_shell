#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

typedef struct
{
	char **av;
	char *cmd;
	const char *shell_name;
} data;

/**
 * helpers.c
 */
void _puts(const char *str);
void free_array(char **array);
void split(data *d, const char *delim);
void init_data(data *d, const char *shell_name);
void read_cmd(data *d);

/**
 * exec.c
 */
void start_process(data *d);
void handler_sigint(int sig);
void _exec(data *d);

#endif