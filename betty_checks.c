#include <stdio.h>
#include <stdlib.h>

/**
 * main - Entry point of the program
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
        int i;
        char *str;

        str = malloc(10 * sizeof(char));
        if (str == NULL)
        {
                printf("Failed to allocate memory\n");
                return (1);
        }

        for (i = 0; i < 10; i++)
                str[i] = 'a';

        printf("String: %s\n", str);

        free(str);

        return (0);
}

