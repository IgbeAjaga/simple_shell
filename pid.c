#include "shell.h"

/**
 * get_parent_pid - Get the PID of the parent process
 *
 * Return: The PID of the parent process
 */
pid_t get_parent_pid(void)
{
    return getppid();
}

