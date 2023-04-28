#include "main.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_functions_ret = 0;

	while (r != -1 && builtin_functions_ret != -2)
	{
		initialize_info(info);
		if (interactive_mode(info))
			_print_string("$ ");
		error_print_char(BUFF_FLUSH);
		r = read_input(info);
		if (r != -1)
		{
			fill_info(info, av);
			builtin_functions_ret = find_builtin_command(info);
			if (builtin_functions_ret == -1)
				find_command(info);
		}
		else if (interactive_mode(info))
			_print_char('\n');
		_info_free(info, 0);
	}
	writeHistoryToFile(info);
	_info_free(info, 1);
	if (!interactive_mode(info) && info->status)
		exit(info->status);
	if (builtin_functions_ret == -2)
	{
		if (info->or == -1)
			exit(info->status);
		exit(info->or);
	}
	return (builtin_functions_ret);
}

/**
 * find_builtin_command - finds a builtin_functions command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin_functions not found,
 *	0 if builtin_functions executed successfully,
 *	1 if builtin_functions found but not successful,
 *	2 if builtin_functions signals exit()
 */
int find_builtin_command(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_functions_table builtin_functionstbl[] = {
		{"exit", _exit_shell},
		{"env", print_env},
		{"help", _display_help},
		{"history", history_builtin},
		{"setenv", set_env_var},
		{"unsetenv", unset_env_var},
		{"cd", _change_directory},
		{"alias", alias_builtin},
		{NULL, NULL}
	};

	for (i = 0; builtin_functionstbl[i].type; i++)
		if (str_compare(info->argv[0], builtin_functionstbl[i].type) == 0)
		{
			info->line_counter++;
			built_in_ret = builtin_functionstbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_command - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_command(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecounterflag == 1)
	{
		info->line_counter++;
		info->linecounterflag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delimiter(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info, get_env_var(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_command(info);
	}
	else
	{
		if ((interactive_mode(info) || get_env_var(info, "PATH=")
					|| info->argv[0][0] == '/') && is_command(info, info->argv[0]))
			fork_command(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_errors(info, "not found\n");
		}
	}
}

/**
 * fork_command - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_command(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environment_variables(info)) == -1)
		{
			_info_free(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_errors(info, "Permission denied\n");
		}
	}
}
