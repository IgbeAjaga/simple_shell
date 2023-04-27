#include "shell.h"

/**
 * _unsetenv - remove an environment variable
 * @name: name of the variable to remove
 *
 * Return: 0 on success, -1 on failure
 */
int _unsetenv(const char *name)
{
	int i, j, len;
	char **new_env;

	if (name == NULL || *name == '\0' || strchr(name, '=') != NULL)
	{
    	fprintf(stderr, "Invalid argument\n");
    	return (-1);
	}

	len = _strlen(name);

	for (i = 0; environ[i] != NULL; i++)
	{
    	if (_strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
    	{
        	/* Remove the variable by shifting all subsequent ones */
        	for (j = i; environ[j] != NULL; j++)
            	environ[j] = environ[j + 1];
        	break;
    	}
	}

	/* Allocate a new environment variable array without the removed variable */
	new_env = malloc(sizeof(char *) * (i + 1));
	if (new_env == NULL)
	{
    	perror("malloc");
    	return (-1);
	}

	for (j = 0; j < i; j++)
    	new_env[j] = environ[j];

	new_env[j] = NULL;
	environ = new_env;

	return (0);
}

