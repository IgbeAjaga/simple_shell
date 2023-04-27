#include "shell.h"

char *read_line(void)
{
	int buffer_size = BUFFER_SIZE;
	char *buffer = malloc(sizeof(char) * buffer_size);
	int position = 0;
	int character;

	if (!buffer) {
    	perror("allocation error");
    	exit(EXIT_FAILURE);
	}

	while (1) {
    	character = getchar();

    	if (character == EOF || character == '\n') {
        	buffer[position] = '\0';
        	return buffer;
    	} else {
        	buffer[position] = character;
    	}

    	position++;

    	if (position >= buffer_size) {
        	buffer_size += BUFFER_SIZE;
        	buffer = realloc(buffer, sizeof(char) * buffer_size);

        	if (!buffer) {
            	perror("allocation error");
            	exit(EXIT_FAILURE);
        	}
    	}
	}
}

char **split_line(char *line)
{
	int buffer_size = BUFFER_SIZE;
	char **tokens = malloc(sizeof(char*) * buffer_size);
	char *token;
	int position = 0;

	if (!tokens) {
    	perror("allocation error");
    	exit(EXIT_FAILURE);
	}

	token = strtok(line, TOKEN_DELIMITERS);

	while (token != NULL) {
    	if (token[0] != COMMENT_CHARACTER) {
        	tokens[position] = token;
        	position++;

        	if (position >= buffer_size) {
            	buffer_size += BUFFER_SIZE;
            	tokens = realloc(tokens, sizeof(char*) * buffer_size);

            	if (!tokens) {
                	perror("allocation error");
                	exit(EXIT_FAILURE);
            	}
        	}
    	}

    	token = strtok(NULL, TOKEN_DELIMITERS);
	}

	tokens[position] = NULL;
	return tokens;
}

int execute(char **args)
{
	pid_t pid;
	int status;

	if (args[0] == NULL) {
    	return 1;
	}

	pid = fork();

	if (pid == 0) {
    	if (execvp(args[0], args) == -1) {
        	perror("execution error");
    	}

    	exit(EXIT_FAILURE);
	} else if (pid < 0) {
    	perror("fork error");
	} else {
    	do {
        	waitpid(pid, &status, WUNTRACED);
    	} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return 1;
}

