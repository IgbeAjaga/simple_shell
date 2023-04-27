#ifndef SHELL_H
#define SHELL_H
<<<<<<< HEAD

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

/* Function prototypes */
char *read_line(void);
char **split_line(char *line);
int execute_command(char **args);
void print_error(char *msg);
void print_prompt(void);
void handle_signal(int sig);
pid_t get_parent_pid(void);

#endif /* SHELL_H */

=======
 
/* Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
 
#define BUFFER_SIZE 1024
#define TOKEN_DELIMITERS " \t\r\n\a"
#define COMMENT_CHARACTER '#'
#define BUFFER_SIZE 1024
#define DELIMITERS " \t\r\n\a"
#define READ_SIZE 1024
#define MAX_COMMAND_LENGTH 1024
#define MAX_ALIAS_COUNT 100
#define MAX_ALIAS_NAME_LENGTH 100
#define MAX_ALIAS_VALUE_LENGTH 1000
 
/* Global Variables */
extern char **environ;
/* Function Prototypes */
int env_builtin(void);
/* Utility Function Prototypes */
int _putchar(char c);
int _strlen(char *s);
int execute_command(char **args);
char **split_line(char *line);
int shell_loop(void);
char *read_line(void);
char **split_line(char *line);
int execute(char **args);
int execute_command(char *command);
void display_prompt(void);
char *read_input(void);
char **parse_input(char *input);
int execute_command(char **args);
void free_memory(char **args);
char *path[MAX_PATHS];
char **split_line(char *line)
void get_path();
char **split_input(char *input);
int env_builtin(void);
char *getline(void);
char **split_string(char *str);
int sh_exit(char **args);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);
void handle_commands(char *commands);
int execute_command(char **args);
void print_aliases();
void print_selected_aliases(char **names);
void add_alias(char *name, char *value);
void parse_args(int argc, char **argv);
int main(int argc, char **argv);
char *replace_vars(char *str, int status, pid_t pid);
int execute(char **args);
size_t _strlen(char *s);
int interactive(information_t *information);
int is_delimiter(char b, char *delimiter);
int _isalpha(int c);
int _atoi(char *s);
 
typedef struct {
        	char name[MAX_ALIAS_NAME_LENGTH];
        	char value[MAX_ALIAS_VALUE_LENGTH];
} alias_t;
 
#endif /* SHELL_H */


>>>>>>> f9259c623b01501c69f1bd2f5e7cc4547ed1f685
