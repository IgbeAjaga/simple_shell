#include “shell.h”
 #include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

void display_prompt(void);
char *read_input(void);
char **parse_input(char *input);
int execute_command(char **args);
void free_memory(char **args);

int main(void)
{
	char *input;
	char **args;
	int status;

	do {
    	display_prompt();
    	input = read_input();
    	args = parse_input(input);
    	status = execute_command(args);
    	free_memory(args);
    	free(input);
	} while (status);

	return 0;
}

void display_prompt(void)
{
	perror("$ ");
}

char *read_input(void)
{
	char *input = NULL;
	size_t len = 0;
	ssize_t nread;

	nread = getline(&input, &len, stdin);
	if (nread == -1) {
    	if (feof(stdin)) {
        	exit(EXIT_SUCCESS);
    	} else {
        	perror("read_input");
        	exit(EXIT_FAILURE);
    	}
	}

	input[strcspn(input, "\n")] = '\0';  // Remove trailing newline
	return input;
}

char **parse_input(char *input)
{
	const char *delim = " \t\n";
	char *token;
	char **args = malloc(BUFFER_SIZE * sizeof(char *));
	int i = 0;

	if (!args) {
    	perror("parse_input");
    	exit(EXIT_FAILURE);
	}

	token = strtok(input, delim);
	while (token != NULL) {
    	args[i++] = token;
    	token = strtok(NULL, delim);
	}
	args[i] = NULL;

	return args;
}

int execute_command(char **args)
{
	pid_t pid;
	int status;

	if (args[0] == NULL) {
    	return 1;  // Empty command
	}

	pid = fork();
	if (pid == -1) {
    	perror("execute_command");
    	exit(EXIT_FAILURE);
	} else if (pid == 0) {
    	// Child process
    	if (execvp(args[0], args) == -1) {
        	perror("execute_command");
        	exit(EXIT_FAILURE);
    	}
    	exit(EXIT_SUCCESS);
	} else {
    	// Parent process
    	do {
        	if (waitpid(pid, &status, WUNTRACED) == -1) {
            	perror("execute_command");
            	exit(EXIT_FAILURE);
        	}
    	} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return 1;
}

void free_memory(char **args)
{
	free(args);
}

