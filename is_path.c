#include "main.h"

/**
 * compare_args - Check command in path
 *
 * @Arg_str: argument string.
 * @ct_output: output.
 *
 * Return: output;
 */

int compare_args(char **Arg_str, int ct_output)
{
	int cal_path = 0;
	struct stat st;
	char *copy_Arg = NULL;

	copy_Arg = malloc(sizeof(char *) * string_length(Arg_str[0]));
	string_copy(copy_Arg, Arg_str[0]);

	if (stat(Arg_str[0], &st) == 0 && copy_Arg[0] != '/')
		Arg_str[0] = check_path(Arg_str);

	else if (stat(Arg_str[0], &st) == -1)
		Arg_str[0] = check_path(Arg_str);

	if (string_compare(copy_Arg, Arg_str[0]) != 0)
		cal_path = 1;

	if (stat(Arg_str[0], &st) == 0)
		ct_output = run(Arg_str, ct_output);

	else
	{
		print_error(Arg_str[0]);
		ct_output = 127;
	}

	if (cal_path == 1)
		free(Arg_str[0]);

	free(copy_Arg);

	return (ct_output);
}
