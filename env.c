#include <stdio.h>

/**
 * main - prints the address of env and environ
 * @argc: the number of command-line arguments
 * @argv: an array of pointers to the command-line arguments
 * @env: an array of pointers to the environment variables
 *
 * Return: Always 0.
 */
int main(int argc, char **argv, char **env)
{
	printf("The address of env is: %p\n", (void *)&env);
	printf("The address of environ is: %p\n", (void *)&environ);

	return (0);
}
