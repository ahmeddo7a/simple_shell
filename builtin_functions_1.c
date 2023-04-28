#include "main.h"

/**
 * history_builtin - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int history_builtin(info_t *info)
{
	print_mylist(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *p, ch;
	int ret;

	p = find_char(str, '=');
	if (!p)
		return (1);
	ch = *p;
	*p = 0;
	ret = del_node_at_index(&(info->alias),
		get_index_of_node(info->alias, node_starts_with(info->alias, str, -1)));
	*p = ch;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = find_char(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_end_node(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_of_items *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = find_char(node->str, '=');
		for (a = node->str; a <= p; a++)
		_print_char(*a);
		_print_char('\'');
		_print_string(p + 1);
		_print_string("'\n");
		return (0);
	}
	return (1);
}

/**
 * alias_builtin - mimics the alias builtin_functions (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int alias_builtin(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_of_items *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = find_char(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
