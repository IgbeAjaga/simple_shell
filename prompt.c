#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define EOF_RECEIVED "EOF_RECEIVED"
#define PROMPT "$ "

/**
 * readline - Reads a line from stdin
 *
 * Return: A pointer to a string containing the read line or NULL if EOF was
 * encountered
 */
char *readline(void)
{
	char *buffer = malloc(BUFFER_SIZE);

	if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
	{
		free(buffer);
		buffer = malloc(sizeof(EOF_RECEIVED));
		strcpy(buffer, EOF_RECEIVED);
		return (buffer);
	}
	buffer[strcspn(buffer, "\n")] = '\0';
	return (buffer);
}

/**
 * main - Runs the shell program
 *
 * Return: Always returns 0
 */
int main(void)
{
	char *line;

	printf(PROMPT);
	while ((line = readline()) != NULL && strcmp(line, EOF_RECEIVED) != 0)
	{
		printf("%s\n" PROMPT, line);
		free(line);
	}
	if (line != NULL)
		free(line);

	printf("\n");
	return (0);
}

