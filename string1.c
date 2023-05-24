#include "shell.h"


/**
 * _strcpy - Duplicates string.
 * @dest: Destination
 * @src: source.
 *
 * Return: pointer to dest.
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == NULL)
		return (dest);

	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}


/**
 * _strdup - Duplicates string.
 * @str: String to duplicate.
 *
 * Return: pointer to the string duplicated
 */
char *_strdup(const char *str)
{
	if (str == NULL)
		return (NULL);

	size_t length;

	length = strlen(str);

	char *ret = malloc((length + 1) * sizeof(char));

	if (ret == NULL)
		return (NULL);

	return (strcpy(ret, str));
}


/**
 * _puts - Prints input string.
 * @str: String to print.
 *
 * Return: Nothing.
 */
void _puts(char *str)
{
	int i = 0;

	if (str == NULL)
		return;


	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}


/**
 * _putchar - Writes the Char. c to stdout.
 * @c: The Character to be printed.
 *
 * Return: 1 On Success, On error, -1 is returned, and errno is set correctly.
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}
