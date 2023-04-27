#include "shell.h"
int main(int argc, char *argv[])
{
	char *line;
	char **args;
	int status;
 do {
    	perror("$ ");
    	line = read_line();
    	args = split_line(line);
    	status = execute(args);
    	free(line);
    	free(args);
	} while (status);
 
	return EXIT_SUCCESS;
}
  
int main(int argc, char **argv)
{
	/* Run command loop */
	shell_loop();
 
	/* Exit */
	return EXIT_SUCCESS;
}
 /* handle comment */
int main(void)
{
	char *line;
	char **args;
	int status;
 
	do {
    	perror("$ ");
    	line = read_line();
    	args = split_line(line);
    	status = execute(args);
 
    	free(line);
    	free(args);
	} while (status);
 
	return EXIT_SUCCESS;
}
 
/**
 * main - entry point for the simple shell program
 * @argc: the argument count
 * @argv: the argument vector
 *
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char **argv)
{
    	FILE *file;
    	char *line = NULL;
    	size_t len = 0;
    	ssize_t read;
    	int status = 0;
 
    	if (argc != 2)
    	{
            	perror(stderr, "Usage: %s filename\n", argv[0]);
            	return (1);
    	}
 
    	file = fopen(argv[1], "r");
    	if (!file)
    	{
            	perror("fopen");
            	return (1);
    	}
 
    	while ((read = getline(&line, &len, file)) != -1)
    	{
            	/* ignore comments */
         	   if (line[0] == '#')
                    	continue;
 
            	/* remove trailing newline */
            	if (line[read - 1] == '\n')
                    	line[read - 1] = '\0';
 
            	/* execute the command */
            	status = execute_command(line);
            	if (status != 0)
            	{
                    	perror(stderr, "Error: command returned %d\n", status);
                    	break;
            	}
    	}
 
    	if (line)
            	free(line);
 
    	fclose(file);
 
    	return (status);
}

