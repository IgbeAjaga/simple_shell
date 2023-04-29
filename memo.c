#include "shell.h"

/**
 * bfree -  address allocationpointer
 * @ptr: ptr
 *
 * Return: if succesul return 1,else 0;
 */

int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
