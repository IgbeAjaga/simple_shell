#include "shell.h"

char *path[MAX_PATHS];

char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	getline(&line, &bufsize, stdin);
	return line;
}

char **split_line(char *line)
{
	int i = 0;
	char *token;
	char **tokens = malloc(MAX_ARGS * sizeof(char *));

	if (!tokens) {
    	perror("malloc error");
    	exit(EXIT_FAILURE);
	}

	token = strtok(line, " \t\r\n");
	while (token != NULL) {
    	tokens[i] = token;
    	i++;
    	token = strtok(NULL, " \t\r\n");
	}

	tokens[i] = NULL;
	return tokens;
}

void get_path()
{
	int i = 0;
	char *path_var = getenv("PATH");
	char *token = strtok(path_var, ":");

	while (token != NULL) {
    	path[i] = token;
    	i++;
    	token = strtok(NULL, ":");
	}

	path[i] = NULL;
}

char *find_executable(char *command)
{
	int i = 0;
	char *full_path = malloc(MAX_LINE * sizeof(char));

	while (path[i] != NULL) {
    	snprintf(full_path, MAX_LINE, "%s/%s", path[i], command);
    	if (access(full_path, X_OK) == 0) {
        	return full_path;
    	}
    	i++;
	}

	free(full_path);
	return NULL;
}

int execute(char **args)
{
	pid_t pid, wpid;
	int status;

	if (args[0] == NULL) {
    	return 1;
	}

	if (strcmp(args[0], "exit") == 0) {
    	return 0;
	}

	get_path();
	char *executable_path = find_executable(args[0]);

	if (executable_path == NULL) {
    	perror("%s: command not found\n", args[0]);
    	return 1;
	}

	pid = fork();
	if (pid == 0) {
    	execve(executable_path, args, environ);
    	perror("execve error");
    	exit(EXIT_FAILURE);
	} else if (pid < 0) {
    	perror("fork error");
    	exit(EXIT_FAILURE);
	} else {
    	do {
        	wpid = waitpid(pid, &status, WUNTRACED);
    	} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	free(executable_path);
	return 1;
}

