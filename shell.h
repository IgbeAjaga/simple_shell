#ifndef SHELL_H
#define SHELL_H

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

