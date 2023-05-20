#include "main.h"

/**
 * _getenv - retrieves the value of an environment variable.
 * @name: string input
 * @env: environment variable
 * Return: value of an environment variable
 */

char *_getenv(char **env, char *name)
{
	int i = -1;
	size_t name_len;

	if (name == NULL || *name == '\0')
		return (NULL);
	if (env == NULL)
		return (NULL);

	name_len = _strlen(name);

	while (env[++i])
	{
		if (strncmp(env[i], name, name_len) == 0)
		{
			return (env[i] + name_len + 1);
		}
	}
	return (NULL);
}

/**
 * _which - locate the executable file associated with a given command.
 * @d: string input
 * Return: void
 */
int _which(data *d)
{
	char *token, *path, *paths = malloc(_strlen(_getenv(d->env, "PATH")) + 1);
	size_t token_len;
	int find = -1;

	strcpy(paths, _getenv(d->env, "PATH"));
	if (paths == NULL)
		return (find);
	token = strtok(paths, ":");
	while (token)
	{
		token_len = _strlen(token) + _strlen(d->av[0]) + 2;
		path = malloc(token_len);
		if (path == NULL)
			return (find);
		strcpy(path, token);
		strcat(path, "/");
		strcat(path,  d->av[0]);
		if (access(path, X_OK) == 0)
		{
			free(d->av[0]);
			d->av[0] = strdup(path);
			free(path);
			find = 0;
			break;
		}
		free(path);
		token = strtok(NULL, ":");
	}
	free(paths);
	return (find);
}
