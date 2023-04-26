#include "main.h"

/**
 * main - start shell.
 *
 * Return: (0).
 */

int main(void)
{
	char *row = NULL;
	char **tokens = NULL;
	int ct_output = 0;

	while (1)
	{
		if (isatty(STDIN))
		write(STDOUT, "#alx$ ", 7);

		row = read_row();
		tokens = tokenizer(row);
		ct_output = execute(tokens, ct_output, row);

		free(row);
		free(tokens);
	}
	return (0);
}
