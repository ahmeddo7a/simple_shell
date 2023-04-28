#include "main.h"

/**
 * string_copy - copies a string
 * @destination: the destinationination
 * @src_str: the source
 *
 * Return: pointer to destinationination
 */
char *string_copy(char *destination, char *src_str)
{
	int i = 0;

	if (destination == src_str || src_str == 0)
		return (destination);
	while (src_str[i])
	{
		destination[i] = src_str[i];
		i++;
	}
	destination[i] = 0;
	return (destination);
}

/**
 * string_duplicate - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *string_duplicate(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * _print_string - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _print_string(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		_print_char(str[j]);
		j++;
	}
}

/**
 * _print_char - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _print_char(char c)
{
	static int q;
	static char buf[WRITE_BUFF];

	if (c == BUFF_FLUSH || q >= WRITE_BUFF)
	{
		write(1, buf, q);
		q = 0;
	}
	if (c != BUFF_FLUSH)
		buf[q++] = c;
	return (1);
}
