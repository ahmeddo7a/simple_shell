#include "main.h"

/**
 * is_variable_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_variable_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->command_buff_type = COMMAND_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->command_buff_type = COMMAND_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->command_buff_type = COMMAND_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * validate_variable_chain - checks we should continue chaining
 * based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void validate_variable_chain(info_t *info,
		char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->command_buff_type == COMMAND_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->command_buff_type == COMMAND_OR)
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
 * alias_replacement - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int alias_replacement(info_t *info)
{
	int i;
	list_of_items *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = find_char(node->str, '=');
		if (!p)
			return (0);
		p = string_duplicate(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * variables_replacement - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int variables_replacement(info_t *info)
{
	int i = 0;
	list_of_items *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!str_compare(info->argv[i], "$?"))
		{
			str_replacement(&(info->argv[i]),
					string_duplicate(number_conversion(info->status, 10, 0)));
			continue;
		}
		if (!str_compare(info->argv[i], "$$"))
		{
			str_replacement(&(info->argv[i]),
					string_duplicate(number_conversion(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			str_replacement(&(info->argv[i]),
					string_duplicate(find_char(node->str, '=') + 1));
			continue;
		}
		str_replacement(&info->argv[i], string_duplicate(""));

	}
	return (0);
}

/**
 * str_replacement - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int str_replacement(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
