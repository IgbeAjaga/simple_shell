#include "shell.h"

/**
 * replace_vars - Replace variables in a string with their respective values
 * @str: The string to process
 * @status: The exit status of the last executed command
 * @pid: The process ID of the shell
 *
 * Return: The processed string, or NULL on failure
 */
char *replace_vars(char *str, int status, pid_t pid)
{
	char *var, *val, *new_str, *tmp;
	size_t size = 0;

	if (!str)
    	return (NULL);

	new_str = malloc(sizeof(char) * (strlen(str) + 1));
	if (!new_str)
    	return (NULL);

	while (*str)
	{
    	if (*str == '$')
    	{
        	str++;

        	if (*str == '$')
        	{
            	asprintf(&val, "%d", pid);
            	size += strlen(val);
            	tmp = new_str;
            	new_str = realloc(new_str, size + 1);
            	if (!new_str)
                	return (NULL);
            	sprintf(new_str + strlen(new_str), "%s", val);
            	free(val);
        	}
        	else if (*str == '?')
        	{
            	asprintf(&val, "%d", status);
            	size += strlen(val);
            	tmp = new_str;
            	new_str = realloc(new_str, size + 1);
            	if (!new_str)
                	return (NULL);
            	sprintf(new_str + strlen(new_str), "%s", val);
            	free(val);
        	}
        	else if (*str == '{')
        	{
            	var = str + 1;
            	str = strchr(str, '}');
            	if (!str)
                	return (NULL);
            	*str = '\0';

            	val = getenv(var);
            	if (!val)
                	val = "";

            	size += strlen(val);
            	tmp = new_str;
            	new_str = realloc(new_str, size + 1);
            	if (!new_str)
                	return (NULL);
            	sprintf(new_str + strlen(new_str), "%s", val);
        	}
        	else if (isdigit(*str))
        	{
            	int index = atoi(str);
            	if (index >= optind)
            	{
                	return (NULL);
            	}
            	else if (optind - index <= argc - 1)
            	{
                	val = argv[optind - index];
                	size += strlen(val);
                	tmp = new_str;
                	new_str = realloc(new_str, size + 1);
                	if (!new_str)
                    	return (NULL);
                	sprintf(new_str + strlen(new_str), "%s", val);
            	}
            	else
            	{
                	return (NULL);
            	}
        	}
        	else if (isalpha(*str) || *str == '_')
        	{
            	var = str;
            	str += strcspn(str, DELIM);

            	tmp = *str;
            	*str = '\0';
            	val = getenv(var);
            	*str = tmp;

            	if (!val)
                	val = "";

            	size += strlen(val);
            	tmp = new_str;
            	new_str = realloc(new_str, size + 1);
            	if (!new_str)
                	return (NULL);
            	sprintf(new_str + strlen(new_str), "%s", val);
        	}
        	else
        	{
            	return (NULL);
        	}
    	}
    	else
    	{
        	tmp = new_str;
        	new_str = realloc(new_str,

}

