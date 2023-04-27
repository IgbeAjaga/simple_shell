#include “shell.h”

#define MAX_COMMAND_LENGTH 1024

/* Function to parse a command and execute it */
void execute_command(char *command) {
	char *args[MAX_COMMAND_LENGTH];
	char *token;
	int arg_index = 0;
    
	/* Tokenize the command */
	token = strtok(command, " ");
	while (token != NULL) {
    	args[arg_index++] = token;
    	token = strtok(NULL, " ");
	}
	args[arg_index] = NULL;
    
	/* Execute the command */
	if (execvp(args[0], args) == -1) {
    	perror("Error executing command");
    	exit(EXIT_FAILURE);
	}
}

/* Function to handle a list of commands separated by ; */
void handle_commands(char *commands) {
	char *command;
	pid_t pid;
	int status;
    
	/* Tokenize the commands */
	command = strtok(commands, ";");
	while (command != NULL) {
    	/* Fork a new process */
    	pid = fork();
    	if (pid == 0) {
        	/* Child process: execute the command */
        	execute_command(command);
    	} else if (pid < 0) {
        	perror("Error forking process");
        	exit(EXIT_FAILURE);
    	} else {
        	/* Parent process: wait for the child to finish */
        	waitpid(pid, &status, 0);
    	}
   	 
    	/* Move to the next command */
    	command = strtok(NULL, ";");
	}
}

int main(void) {
	char command[MAX_COMMAND_LENGTH];
	char cwd[MAX_COMMAND_LENGTH];

	while (1) {
    	/* Get the current working directory and print the shell prompt */
    	if (getcwd(cwd, sizeof(cwd)) != NULL) {
        	printf("%s$ ", cwd);
    	} else {
        	perror("Error getting current working directory");
        	exit(EXIT_FAILURE);
    	}
   	 
    	/* Read a command from the user */
    	if (fgets(command, sizeof(command), stdin) != NULL) {
        	/* Remove the newline character at the end of the command */
        	command[strcspn(command, "\n")] = '\0';
       	 
        	/* Handle the commands */
        	handle_commands(command);
    	}
	}
    
	return 0;
}


