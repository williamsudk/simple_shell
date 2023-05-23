#include "shell.h"



/**
 * _strlen - Returns Length of String.
 * @s: String Length to check.
 *
 * Return: Integer Length of string.
 */
int _strlen(char *s)
{
	char *ptr = s;

	while (*ptr)
		ptr++;

	return (ptr - s);
}


/**
 * _strcmp - Execute alphabetic comparison of two strings.
 * @s1: 1st string.
 * @s2: 2nd string.
 *
 * Return: Negative if s1 is less than s2,
 *         Positive if s1 is greater than s2, 0 if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	register unsigned char *ptr1 = (unsigned char *)s1;
	register unsigned char *ptr2 = (unsigned char *)s2;

	while (*ptr1 && (*ptr1 == *ptr2))
	{
		ptr1++;
		ptr2++;
	}

	return (*ptr1 - *ptr2);
}


/**
 * starts_with - finds out if needle begins with haystack.
 * @haystack: String to search.
 * @needle: Substring to find.
 *
 * Return: Add. of next char of haystack or NULL.
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);

	return ((char *)haystack);
}


/**
 * _strcat - Joins two strings.
 * @dest: destination buffer.
 * @src: source buffer.
 *
 * Return: pointer to destination buffer.
 */
char *_strcat(char *dest, char *src)
{
	char *ptr = dest;

	while (*ptr)
		ptr++;

	while (*src)
		*ptr++ = *src++;

	*ptr = '\0';

	return (dest);
}
