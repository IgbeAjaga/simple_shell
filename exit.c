#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_BUFFER_SIZE 1024
#define DELIMITER " \t\r\n\a"

/* Function to read input from the user */
char *read_input() {
	char *input_buffer = malloc(sizeof(char) * MAX_BUFFER_SIZE);
	if (!input_buffer) {
    	perror("Unable to allocate buffer");
    	exit(EXIT_FAILURE);
	}

	ssize_t bytes_read = getline(&input_buffer, &MAX_BUFFER_SIZE, stdin);
	if (bytes_read == -1) {
    	perror("Unable to read input");
    	exit(EXIT_FAILURE);
	}

	return input_buffer;
}

/* Function to split input into tokens */
char **split_input(char *input) {
	int buffer_size = MAX_BUFFER_SIZE, position = 0;
	char **tokens = malloc(buffer_size * sizeof(char *));
	char *token;

	if (!tokens) {
    	perror("Unable to allocate buffer");
    	exit(EXIT_FAILURE);
	}

	token = strtok(input, DELIMITER);
	while (token != NULL) {
    	tokens[position] = token;
    	position++;

    	if (position >= buffer_size) {
        	buffer_size += MAX_BUFFER_SIZE;
        	tokens = realloc(tokens, buffer_size * sizeof(char *));
        	if (!tokens) {
            	perror("Unable to allocate buffer");
            	exit(EXIT_FAILURE);
        	}
    	}

    	token = strtok(NULL, DELIMITER);
	}
	tokens[position] = NULL;

	return tokens;
}

/* Function to execute commands */
int execute_command(char **args) {
	pid_t pid, wpid;
	int status;

	pid = fork();
	if (pid == 0) {
    	/* Child process */
    	if (execvp(args[0], args) == -1) {
        	perror("Error executing command");
    	}
    	exit(EXIT_FAILURE);
	} else if (pid < 0) {
    	/* Forking error */
    	perror("Error forking");
	} else {
    	/* Parent process */
    	do {
        	wpid = waitpid(pid, &status, WUNTRACED);
    	} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return 1;
}

int main() {
	char *input;
	char **args;
	int status;

	do {
    	perror("my_shell$ ");
    	input = read_input();
    	args = split_input(input);
    	status = execute_command(args);

    	/* Free memory */
    	free(input);
    	free(args);
	} while (status);

	/* Exit the shell */
	exit(EXIT_SUCCESS);
}

