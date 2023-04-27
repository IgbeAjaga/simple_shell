#include "shell.h"

/**
 * env_builtin - Prints the current environment
 * Return: Always returns 0
 */
int env_builtin(void)
{
	unsigned int i;

	for (i = 0; environ[i] != NULL; i++)
    	write(STDOUT_FILENO, environ[i], _strlen(environ[i]));

	return (0);
}
Task 6
getline.c
#include “shell.h”
#include <unistd.h>
#include <stdlib.h>

#define READ_SIZE 1024

/**
 * _getline - reads an entire line from standard input
 * Return: a pointer to the line read, or NULL if an error occurred
 */
char *getline(void)
{
    static char buffer[READ_SIZE];
    static int buffer_index;
    static int buffer_size;
    char *line = NULL;
    int line_index = 0;

    while (1)
    {
   	 /* if the buffer is empty, read from standard input */
   	 if (buffer_index == buffer_size)
   	 {
   		 buffer_size = read(STDIN_FILENO, buffer, READ_SIZE);
   		 buffer_index = 0;

   		 if (buffer_size == -1)
   			 return (NULL);
   		 else if (buffer_size == 0)
   		 {
   			 if (line_index == 0)
   				 return (NULL);
   			 break;
   		 }
   	 }

   	 /* copy characters from the buffer to the line until we reach a newline */
   	 while (buffer_index < buffer_size)
   	 {
   		 if (buffer[buffer_index] == '\n')
   		 {
   			 buffer_index++;
   			 line[line_index] = '\0';
   			 return (line);
   		 }

   		 if (line == NULL)
   		 {
   			 line = malloc(READ_SIZE);
   			 if (line == NULL)
   				 return (NULL);
   		 }
   		 else if (line_index == READ_SIZE - 1)
   		 {
   			 line[line_index] = '\0';
   			 line = realloc(line, READ_SIZE * 2);
   			 if (line == NULL)
   				 return (NULL);
   		 }

   		 line[line_index++] = buffer[buffer_index++];
   	 }
    }

    return (line);
}

