#include "shell.h"


/**
 * list_len - calculates the length of a linked list.
 * @head: a pointer to the 1st node
 *
 * Return: list size.
 */
size_t list_len(const list_t *head)
{
	size_t index = 0;

	while (head)
	{
		head = head->next;
		index++;
	}
	return (index);
}



/**
 * list_to_strings - return an array of strings of list->str
 * @head: a pointer to the 1st node.
 *
 * Return: an array of string.
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}



/**
 * print_list - prints all element of a list_t list.
 * @h: a pointer to 1st node.
 *
 * Return: list size.
 */
size_t print_list(const list_t *h)
{
	size_t index = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		index++;
	}
	return (index);
}


/**
 * node_starts_with - returns the node whose string begins with prefix.
 * @node: a pointer to the list head
 * @prefix: The string to match
 * @c: the Char after prefix to match
 *
 * Return: match node or NULL.
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}



/**
 * get_node_index - gets a nodes index.
 * @head: a pointer to list head.
 * @node: pointer to node
 *
 * Return: -1, or index of node.
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}
