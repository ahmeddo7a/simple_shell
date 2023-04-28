#include "main.h"

/**
 * _atoierror - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 * -1 on error
 */
int _atoierror(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_errors - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 * -1 on error
 */
void print_errors(info_t *info, char *estr)
{
	error_print_string(info->filename);
	error_print_string(": ");
	print_digits(info->line_counter, STDERR_FILENO);
	error_print_string(": ");
	error_print_string(info->argv[0]);
	error_print_string(": ");
	error_print_string(estr);
}

/**
 * print_digits - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_digits(int input, int fd)
{
	int (*print_char_)(char) = _print_char;
	int i, count = 0;
	unsigned int _abs, current;

	if (fd == STDERR_FILENO)
		print_char_ = error_print_char;
	if (input < 0)
	{
		_abs = -input;
		print_char_('-');
		count++;
	}
	else
		_abs = input;
	current = _abs;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs / i)
		{
			print_char_('0' + current / i);
			count++;
		}
		current %= i;
	}
	print_char_('0' + current);
	count++;

	return (count);
}

/**
 * number_conversion - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *number_conversion(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * rm_comment - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void rm_comment(char *buf)
{
	int n;

	for (n = 0; buf[n] != '\0'; n++)
		if (buf[n] == '#' && (!n || buf[n - 1] == ' '))
		{
			buf[n] = '\0';
			break;
		}
}
