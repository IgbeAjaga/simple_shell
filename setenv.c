#include “shell.h”
 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * _setenv - initialize a new environment variable, or modify an existing one
 * @name: name of the variable to set
 * @value: value to set the variable to
 * @overwrite: flag to indicate whether to overwrite an existing variable
 *
 * Return: 0 on success, -1 on failure
 */
int _setenv(const char *name, const char *value, int overwrite)
{
    	int len, ret;
    	char *var;

    	if (name == NULL || *name == '\0' || strchr(name, '=') != NULL) {
            	fprintf(stderr, "Invalid argument to setenv\n");
            	return (-1);
    	}

    	len = strlen(name) + strlen(value) + 2;
    	var = malloc(len);
    	if (var == NULL) {
            	perror("setenv");
            	return (-1);
    	}

    	ret = snprintf(var, len, "%s=%s", name, value);
    	if (ret < 0 || ret >= len) {
            	fprintf(stderr, "Failed to set environment variable\n");
            	free(var);
            	return (-1);
    	}

    	ret = overwrite ? 0 : 1;
    	ret = putenv(var);
    	if (ret != 0) {
            	perror("setenv");
            	free(var);
            	return (-1);
    	}

    	return (0);
}

