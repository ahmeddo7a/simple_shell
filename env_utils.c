#include "main.h"

/**
 * get_environment_variables - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environment_variables(info_t *info)
{
	if (!info->environ || info->environ_changed)
	{
		info->environ = str_list_of_items(info->env);
		info->environ_changed = 0;
	}

	return (info->environ);
}

/**
 * unset_environment_variable - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int unset_environment_variable(info_t *info, char *var)
{
	list_of_items *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = str_starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->environ_changed = del_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->environ_changed);
}

/**
 * set_environment_variable - Initialize a new environment variable,
 * or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int set_environment_variable(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_of_items *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(str_length(var) + str_length(value) + 2);
	if (!buf)
		return (1);
	string_copy(buf, var);
	str_concatenate(buf, "=");
	str_concatenate(buf, value);
	node = info->env;
	while (node)
	{
		p = str_starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->environ_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_end_node(&(info->env), buf, 0);
	free(buf);
	info->environ_changed = 1;
	return (0);
}
