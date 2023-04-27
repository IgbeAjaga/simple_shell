#include “shell.h”
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

void display_prompt(void);
char *read_input(void);
char **parse_input(char *input);
int execute_command(char **args);
void free_memory(char **args);

int main(void) {
	char *input, **args;
	int status;

	do {
    	display_prompt();
    	input = read_input();
    	args = parse_input(input);
    	status = execute_command(args);

    	free(input);
    	free_memory(args);
	} while (status);

	return 0;
}

void display_prompt(void) {
	perror("$ ");
}

char *read_input(void) {
	char *input = NULL;
	size_t buffer_size = BUFFER_SIZE;

	getline(&input, &buffer_size, stdin);
	return input;
}

char **parse_input(char *input) {
	char **args = NULL;
	char *token = strtok(input, " \n");
	int i = 0;

	while (token != NULL) {
    	args = realloc(args, sizeof(char *) * (i+1));
    	args[i] = strdup(token);
    	i++;

    	token = strtok(NULL, " \n");
	}

	args = realloc(args, sizeof(char *) * (i+1));
	args[i] = NULL;

	return args;
}

int execute_command(char **args) {
	pid_t pid;
	int status;

	if (args[0] == NULL) {
    	return 1;
	}

	pid = fork();

	if (pid == 0) {
    	if (execvp(args[0], args) == -1) {
        	perror("simple_shell");
    	}
    	exit(EXIT_FAILURE);
	} else if (pid < 0) {
    	perror("simple_shell");
	} else {
    	do {
        	waitpid(pid, &status, WUNTRACED);
    	} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return 1;
}

void free_memory(char **args) {
	for (int i = 0; args[i] != NULL; i++) {
    	free(args[i]);
	}
	free(args);
}

