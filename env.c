#include "main.h"

/**
 * print_env - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int print_env(info_t *info)
{
	print_mylist_of_strings(info->env);
	return (0);
}

/**
 * get_env_var - gets the value of an environ variable
 * @info: Structure containing potential arguments.
 * @name: env var name
 *
 * Return: the value
 */
char *get_env_var(info_t *info, const char *name)
{
	list_of_items *node = info->env;
	char *p;

	while (node)
	{
		p = str_starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * set_env_var - Initialize a new environment variable,
 * or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int set_env_var(info_t *info)
{
	if (info->argc != 3)
	{
		error_print_string("Incorrect number of arguements\n");
		return (1);
	}
	if (set_environment_variable(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * unset_env_var - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int unset_env_var(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		error_print_string("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		unset_environment_variable(info, info->argv[i]);

	return (0);
}

/**
 * create_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int create_env_list(info_t *info)
{
	list_of_items *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_end_node(&node, environ[i], 0);
	info->env = node;
	return (0);
}
