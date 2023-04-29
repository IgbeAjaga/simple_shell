#include <stdio.h>
#include <unistd.h>

/**
 * main - Printing a quote
 * Return: 1 if success.
 */

int main(void)
{
	write(2, "ALX sleepless nights\" - ALX simple shell project\n", 59);
	return (1);
}
