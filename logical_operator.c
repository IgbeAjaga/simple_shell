#include "shell.h"

int execute_command(char **args)
{
	pid_t pid, wpid;
	int status;

	// Fork process
	pid = fork();
	if (pid == 0) {
    	// Child process
    	if (execvp(args[0], args) == -1) {
        	perror("shell");
    	}
    	exit(EXIT_FAILURE);
	} else if (pid < 0) {
    	// Error forking
    	perror("shell");
	} else {
    	// Parent process
    	do {
        	wpid = waitpid(pid, &status, WUNTRACED);
    	} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	// Return success or failure
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
    	return 1;
	} else {
    	return 0;
	}
}

char **split_line(char *line)
{
	int bufsize = BUFFER_SIZE, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens) {
    	fprintf(stderr, "shell: allocation error\n");
    	exit(EXIT_FAILURE);
	}

	token = strtok(line, DELIMITERS);
	while (token != NULL) {
    	tokens[position] = token;
    	position++;

    	if (position >= bufsize) {
        	bufsize += BUFFER_SIZE;
        	tokens = realloc(tokens, bufsize * sizeof(char *));
        	if (!tokens) {
            	fprintf(stderr, "shell: allocation error\n");
            	exit(EXIT_FAILURE);
        	}
    	}

    	token = strtok(NULL, DELIMITERS);
	}
	tokens[position] = NULL;
	return tokens;
}

int shell_loop(void)
{
	char *line;
	char **args;
	int status;
	int success = 1;

	do {
    	perror("> ");
    	line = NULL;
    	size_t len = 0;
    	getline(&line, &len, stdin);
    	line[strcspn(line, "\n")] = '\0';

    	char *command;
    	while ((command = strsep(&line, ";")) != NULL) {
        	args = split_line(command);
        	if (args[0] != NULL) {
            	if (strcmp(args[0], "exit") == 0) {
                	// Exit shell
                	free(line);
                	free(args);
                	exit(EXIT_SUCCESS);
            	} else if (strcmp(args[0], "cd") == 0) {
                	// Change

