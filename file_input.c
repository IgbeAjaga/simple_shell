#include "shell.h"

/**
 * execute_command - execute a shell command
 * @command: the command to execute
 *
 * Return: the status of the command execution
 */
int execute_command(char *command)
{
    	char *argv[256] = {NULL};
    	char *token;
    	int argc = 0;
    	pid_t pid, wpid;
    	int status;

    	/* tokenize the command */
    	token = strtok(command, " \t\r\n");
    	while (token)
    	{
            	argv[argc] = token;
            	argc++;
            	token = strtok(NULL, " \t\r\n");
    	}

    	if (!argv[0])
            	return (0);

    	/* fork a child process to execute the command */
    	pid = fork();
    	if (pid == -1)
    	{
            	perror("fork");
            	return (1);
    	}
    	else if (pid == 0)
    	{
            	/* execute the command in the child process */
            	execvp(argv[0], argv);
            	perror("execvp");
            	_exit(1);
    	}
    	else
    	{
            	/* wait for the child process to complete */
            	do {
                    	wpid = waitpid(pid, &status, WUNTRACED);
            	} while (!WIFEXITED(status) && !WIFSIGNALED(status));
    	}

    	return (WEXITSTATUS(status));
}

