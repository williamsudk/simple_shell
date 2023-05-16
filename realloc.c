#include "shell.h"



/**
 * _memset - fills up memory with constant byte.
 * @s: pointer to memory area.
 * @b: The byte to fill *s with
 * @n: amount of bytes to be filled
 *
 * Return: (s) pointer to the memory area s.
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}


/**
 * ffree - frees string of strings
 * @pp: The string of strings.
 *
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}



/**
 * _realloc - Reallocates a block of memory.
 * @ptr:  A Pointer to previously malloc'ated block.
 * @old_size: Byte size of old block
 * @new_size: Byte size of new block
 *
 * Return: pointer to the ol'block name.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
