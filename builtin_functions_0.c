#include "main.h"

/**
 * _exit_shell - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int _exit_shell(info_t *info)
{
	int check_exit;

	if (info->argv[1])
	{
		check_exit = _atoierror(info->argv[1]);
		if (check_exit == -1)
		{
			info->status = 2;
			print_errors(info, "Illegal number: ");
			error_print_string(info->argv[1]);
			error_print_char('\n');
			return (1);
		}
		info->or = _atoierror(info->argv[1]);
		return (-2);
	}
	info->or = -1;
	return (-2);
}

/**
 * _change_directory - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _change_directory(info_t *info)
{
	char *s, *dir, buffer[1024];
	int change_dir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_print_string("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = get_env_var(info, "HOME=");
		if (!dir)
			change_dir_ret =
				chdir((dir = get_env_var(info, "PWD=")) ? dir : "/");
		else
			change_dir_ret = chdir(dir);
	}
	else if (str_compare(info->argv[1], "-") == 0)
	{
		if (!get_env_var(info, "OLDPWD="))
		{
			_print_string(s);
			_print_char('\n');
			return (1);
		}
		_print_string(get_env_var(info, "OLDPWD=")), _print_char('\n');
		change_dir_ret =
			chdir((dir = get_env_var(info, "OLDPWD=")) ? dir : "/");
	}
	else
		change_dir_ret = chdir(info->argv[1]);
	if (change_dir_ret == -1)
	{
		print_errors(info, "can't cd to ");
		error_print_string(info->argv[1]), error_print_char('\n');
	}
	else
	{
		set_environment_variable(info, "OLDPWD", get_env_var(info, "PWD="));
		set_environment_variable(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _display_help - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _display_help(info_t *info)
{
	char **array_arg;

	array_arg = info->argv;
	_print_string("help call works. Function not yet implemented \n");
	if (0)
		_print_string(*array_arg);
	return (0);
}
