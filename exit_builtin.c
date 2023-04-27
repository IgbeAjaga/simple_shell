#include "shell.h"

/**
 * sh_exit - exit the shell
 * @args: arguments passed to the function
 * Return: always 0, to signal to exit the shell
 */
int sh_exit(char **args)
{
	if (args[1])
	{
    	int status = atoi(args[1]);

    	if (status == -1)
    	{
        	print_error("Illegal number", args[1]);
        	return (1);
    	}

    	exit(status);
	}

	exit(EXIT_SUCCESS);
}

