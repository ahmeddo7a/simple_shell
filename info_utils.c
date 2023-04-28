#include "main.h"

/**
 * initialize_info - initializes info_t struct
 * @info: struct address
 */
void initialize_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * fill_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void fill_info(info_t *info, char **av)
{
	int i = 0;

	info->filename = av[0];
	if (info->arg)
	{
		info->argv = split_string(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = string_duplicate(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		alias_replacement(info);
		variables_replacement(info);
	}
}

/**
 * _info_free - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void _info_free(info_t *info, int all)
{
	free_strings(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->command_buff)
			free(info->arg);
		if (info->env)
			free_mylist(&(info->env));
		if (info->history)
			free_mylist(&(info->history));
		if (info->alias)
			free_mylist(&(info->alias));
		free_strings(info->environ);
			info->environ = NULL;
		mem_free((void **)info->command_buff);
		if (info->input_file_descriptor > 2)
			close(info->input_file_descriptor);
		_print_char(BUFF_FLUSH);
	}
}
