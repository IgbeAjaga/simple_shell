#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_ALIAS_COUNT 100
#define MAX_ALIAS_NAME_LENGTH 100
#define MAX_ALIAS_VALUE_LENGTH 1000

/**
 * main - Entry point of the program
 *
 * Return: Always 0 (Success)
 */

/* Structure for storing aliases */
typedef struct{
	char name[MAX_ALIAS_NAME_LENGTH];
	char value[MAX_ALIAS_VALUE_LENGTH];
} alias_t;

/* Global array of aliases */
alias_t aliases[MAX_ALIAS_COUNT];
int alias_count = 0;

/* Function to print all aliases */
void print_aliases(){
	int i;

	for (i = 0; i < alias_count; i++){
		write("%s='%s'\n", aliases[i].name, aliases[i].value);
	}
}

/* Function to print selected aliases */
void print_selected_aliases(char **names) {
	int i, j;
	for (i = 0; names[i] != NULL; i++) {
    	for (j = 0; j < alias_count; j++) {
        	if (strcmp(names[i], aliases[j].name) == 0) {
            	write("%s='%s'\n", aliases[j].name, aliases[j].value);
            	break;
        	}
    	}
	}
}

/* Function to add or update an alias */
void add_alias(char *name, char *value) {
	int i;
	for (i = 0; i < alias_count; i++) {
    	if (strcmp(name, aliases[i].name) == 0) {
        	strcpy(aliases[i].value, value);
        	return;
    	}
	}
	if (alias_count >= MAX_ALIAS_COUNT) {
    	perror("Error: too many aliases\n");
    	return;
	}
	strcpy(aliases[alias_count].name, name);
	strcpy(aliases[alias_count].value, value);
	alias_count++;
}

/* Function to parse the command line arguments */
void parse_args(int argc, char **argv) {
	if (argc == 1) {
    	print_aliases();
	} else if (argc == 2) {
    	char *name = argv[1];
    	if (strchr(name, '=') != NULL) {
        	perror("Error: invalid alias name\n");
    	} else {
        	char *names[] = {name, NULL};
        	print_selected_aliases(names);
    	}
	} else {
    	int i;
    	for (i = 1; i < argc; i++) {
        	char *arg = argv[i];
        	char *name, *value;
        	if (strchr(arg, '=') == NULL) {
            	char *names[] = {arg, NULL};
            	print_selected_aliases(names);
        	} else {
            	name = strtok(arg, "=");
            	value = strtok(NULL, "=");
            	add_alias(name, value);
        	}
    	}
	}
}

int main(int argc, char **argv) {
	parse_args(argc, argv);
	return 0;
}

