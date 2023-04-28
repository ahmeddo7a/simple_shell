#include "main.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*mem_free((void **)info->command_buff);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, handle_sigint);
#if USEGETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = get_line(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->linecounterflag = 1;
			rm_comment(*buf);
			buildHistoryList(info, *buf, info->historycounter++);
			/* if (find_char(*buf, ';')) is this a command chain? */
			{
				*len = r;
				info->command_buff = buf;
			}
		}
	}
	return (r);
}

/**
 * read_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t read_input(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_print_char(BUFF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		validate_variable_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_variable_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->command_buff_type = COMMAND_NORM;
		}

		*buf_p = p;
		return (str_length(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->input_file_descriptor, buf, READ_BUFF);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * get_line - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int get_line(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUFF];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = find_char(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _reallocate(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		concat_n_chars(new_p, buf + i, k - i);
	else
		copy_n_chars(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * handle_sigint - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void handle_sigint(__attribute__((unused))int sig_num)
{
	_print_string("\n");
	_print_string("$ ");
	_print_char(BUFF_FLUSH);
}
