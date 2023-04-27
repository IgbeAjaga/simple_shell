#include "shell.h"
 /**
 * cd_builtin - Change current directory of the process
 * @args: Arguments to the command
 * @env: Environment variables
 *
 * Return: Always returns 1, to continue execution
 */
int cd_builtin(char **args, char **env)
{
	char *newdir;
	char cwd[PATH_MAX];
 
	if (args[1] == NULL || _strcmp(args[1], "~") == 0)
	{
    	newdir = _getenv("HOME", env);
    	if (newdir == NULL)
        	return (1);
	}
	else if (_strcmp(args[1], "-") == 0)
	{
    	newdir = _getenv("OLDPWD", env);
    	if (newdir == NULL)
    	{
            print_error("cd: OLDPWD not set", NULL);
        	return (1);
    	}
    	printf("%s\n", newdir);
	}
	else
    	newdir = args[1];
 
	if (chdir(newdir) == -1)
	{
        print_error("cd: can't cd to ", newdir);
    	return (1);
	}
 
    set_env("OLDPWD", getcwd(cwd, sizeof(cwd)), env);
    set_env("PWD", getcwd(cwd, sizeof(cwd)), env);
 
	return (1);
}

