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
	char *shell_name;
} data;

#endif
