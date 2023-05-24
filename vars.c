#include "shell.h"



/**
 * is_chain - Test if current char in buffer is a chain Delimiter.
 * @info: Parametre struct.
 * @buf: char buf.
 * @p: Address of cur. position in buf.
 *
 * Return: 1 if it's a chain Delimiter, or 0 otherwise.
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	switch (buf[j])
	{
		case '|':
			if (buf[j + 1] == '|')
			{
				buf[j] = 0;
				j++;
				info->cmd_buf_type = CMD_OR;
				break;
			}
			return (0);
		case '&':
			if (buf[j + 1] == '&')
			{
				buf[j] = 0;
				j++;
				info->cmd_buf_type = CMD_AND;
				break;
			}
			return (0);

		case ';':
			buf[j] = 0;
			info->cmd_buf_type = CMD_CHAIN;
			break;

		default:
			return (0);
	}

	*p = j;
	return (1);
}



/**
 * check_chain - checks if chaining shoud be continued based on last status.
 * @info: Parameter struct.
 * @buf: Char buf.
 * @p: Add. of current position in buf.
 * @i: Beginining position in buf.
 * @len: length of buf.
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}




/**
 * replace_alias - replaces alias in the tokenized string.
 * @info: Par struct.
 *
 * Return: 1 if replaced, or 0 otherwise.
 */
int replace_alias(info_t *info)
{
	list_t *node;
	char *p;

	while (1)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);

		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);

		p = _strdup(p + 1);
		if (!p)
			return (0);

		info->argv[0] = p;
	}

	return (1);
}


/**
 * replace_vars - Replaces variables in the tokenized string.
 * @info: Parameter struct.
 *
 * Return: 1 if replaced, or 0 otherwise
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]), convert_number(info->status, 10, 0));
			continue;
		}

		if (!_strcmp(info->argv[i], "$$"))

		{
			replace_string(&(info->argv[i]), convert_number(getpid(), 10, 0));
			continue;
		}

		node = node_starts_with(info->env, &(info->argv[i][1]), '=');
		if (node)

		{
			char *value = _strchr(node->str, '=') + 1;

			replace_string(&(info->argv[i]), _strdup(value));
			continue;
		}

		replace_string(&(info->argv[i]), _strdup(""));
	}

	return (1);
}


/**
 * replace_string - this replaces string.
 * @old: Address of old string to replace
 * @new: the new string.
 *
 * Return: 1 if replaced, or 0 otherwise.
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
