#include "shell.h"
#include "shell.h"

/**
 * split_string - Splits a string into an array of words
 * @str: The string to split
 *
 * Return: An array of words, or NULL if str is NULL or memory allocation fails
 */
char **split_string(char *str)
{
	int i, j, len = 0, words = 0;
	char **arr = NULL;

	if (str == NULL)
    	return (NULL);

	for (i = 0; str[i] != '\0'; i++)
	{
    	if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
    	{
        	words++;
        	for (; str[i] != ' ' && str[i] != '\t' && str[i] != '\n' &&
               	str[i] != '\0'; i++)
            	len++;
    	}
	}

	arr = malloc(sizeof(char *) * (words + 1));
	if (arr == NULL)
    	return (NULL);

	for (i = 0, j = 0; j < words; j++)
	{
    	len = 0;
    	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
        	i++;
    	while (str[i + len] != ' ' && str[i + len] != '\t' &&
           	str[i + len] != '\n' && str[i + len] != '\0')
        	len++;
    	arr[j] = malloc(sizeof(char) * (len + 1));
    	if (arr[j] == NULL)
    	{
        	free_array(arr, j);
        	return (NULL);
    	}
    	strncpy(arr[j], &str[i], len);
    	arr[j][len] = '\0';
    	i += len;
	}
	arr[j] = NULL;
	return (arr);
}

/**
 * free_array - Frees an array of strings
 * @arr: The array of strings to free
 * @n: The number of strings in the array
 *
 * Return: None
 */
void free_array(char **arr, int n)
{
	int i;

	for (i = 0; i < n; i++)
    	free(arr[i]);
	free(arr);
}

