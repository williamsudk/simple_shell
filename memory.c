#include "shell.h"



/**
 * bfree - frees Pointer and NULLs the address.
 * @ptr: add. of Pointer to free.
 *
 * Return: 1 if freed, or 0 otherwise.
 */
int bfree(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
