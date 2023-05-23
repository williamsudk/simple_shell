#include "shell.h"


/**
 * strtow - separates string into words.
 * @str: Input string.
 * @d: delimeter string.
 * Return: Pointer to an array of strings, or NULL on Failure.
 */
char **strtow(char *str, char *d)
{
	int v, w, x, z, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (v = 0; str[v] != '\0'; v++)
		if (!is_delim(str[v], d) && (is_delim(str[v + 1], d) || !str[v + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (v = 0, w = 0; w < numwords; w++)
	{
		while (is_delim(str[v], d))
			v++;
		x = 0;
		while (!is_delim(str[v + x], d) && str[v + x])
			x++;
		s[w] = malloc((x + 1) * sizeof(char));
		if (!s[w])
		{
			for (x = 0; x < w; x++)
				free(s[x]);
			free(s);
			return (NULL);
		}
		for (z = 0; z < x; z++)
			s[w][z] = str[v++];
		s[w][z] = 0;
	}
	s[w] = NULL;
	return (s);
}



/**
 * strtow2 - Splits string into words.
 * @str: Input string.
 * @d: delimiter.
 *
 * Return: Pointer to an array of Strings, or NULL on Failure.
 */
char **strtow2(char *str, char d)
{
	int v, w, x, z, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (v = 0; str[v] != '\0'; v++)
		if ((str[v] != d && str[v + 1] == d) ||
				(str[v] != d && !str[v + 1]) || str[v + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (v = 0, w = 0; w < numwords; w++)
	{
		while (str[v] == d && str[v] != d)
			v++;
		x = 0;
		while (str[v + x] != d && str[v + x] && str[v + x] != d)
			x++;
		s[w] = malloc((x + 1) * sizeof(char));
		if (!s[w])
		{
			for (x = 0; x < w; x++)
				free(s[x]);
			free(s);
			return (NULL);
		}
		for (z = 0; z < x; z++)
			s[w][z] = str[v++];
		s[w][z] = 0;
	}
	s[w] = NULL;
	return (s);
}
