#include <stdio.h>
#include <unistd.h>
#include "shell.h"

/**
 * main - PID
 *
 * Return: Always 0.
 */
int main(void)
{
    pid_t my_pid;

    my_pid = get_parent_pid();
    printf("%u\n", my_pid);
    return (0);
}
