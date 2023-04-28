#include "main.h"

/**
 * error_print_string - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void error_print_string(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		error_print_char(str[i]);
		i++;
	}
}

/**
 * error_print_char - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int error_print_char(char c)
{
	static int i;
	static char buf[WRITE_BUFF];

	if (c == BUFF_FLUSH || i >= WRITE_BUFF)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUFF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * write_char_to_fd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int write_char_to_fd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUFF];

	if (c == BUFF_FLUSH || i >= WRITE_BUFF)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUFF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * write_string_to_fd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int write_string_to_fd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += write_char_to_fd(*str++, fd);
	}
	return (i);
}
