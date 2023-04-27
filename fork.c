#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * main - creates 5 child processes that execute the command "ls -l /tmp"
 * using the system() function
 *
 * Return: Always 0.
 */
int main(void)
{
	pid_t pid;
	int status;

	for (int i = 0; i < 5; i++)
	{
		pid = fork();

		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			/* child process */
			system("ls -l /tmp");
			exit(EXIT_SUCCESS);
		}
		else
		{
			/* parent process */
			wait(&status);
		}
	}

	return (0);
}

