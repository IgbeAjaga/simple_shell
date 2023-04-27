#include <stdio.h>

/**
 * main - Prints all the arguments received
 * @ac: Number of arguments
 * @av: Array of arguments
 * Return: Always 0
 */
int main(int ac, char **av)
{
    int i;

    for (i = 0; av[i] != NULL; i++)
    {
        printf("%s\n", av[i]);
    }

    return (0);
}

