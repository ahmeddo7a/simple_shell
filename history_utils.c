#include "main.h"

/**
 * getHistoryFilePath - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *getHistoryFilePath(info_t *info)
{
	char *buf, *dir;

	dir = get_env_var(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (str_length(dir) + str_length(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	string_copy(buf, dir);
	str_concatenate(buf, "/");
	str_concatenate(buf, HIST_FILE);
	return (buf);
}

/**
 * writeHistoryToFile - creates a new file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int writeHistoryToFile(info_t *info)
{
	ssize_t fd;
	char *filename = getHistoryFilePath(info);
	list_of_items *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		write_string_to_fd(node->str, fd);
		write_char_to_fd('\n', fd);
	}
	write_char_to_fd(BUFF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * readHistoryFromFile - reads history from file
 * @info: the parameter struct
 *
 * Return: historycounter on success, 0 otherwise
 */
int readHistoryFromFile(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = getHistoryFilePath(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			buildHistoryList(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		buildHistoryList(info, buf + last, linecount++);
	free(buf);
	info->historycounter = linecount;
	while (info->historycounter-- >= HIST_MAX)
		del_node_at_index(&(info->history), 0);
	renumberHistoryEntries(info);
	return (info->historycounter);
}

/**
 * buildHistoryList - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, historycounter
 *
 * Return: Always 0
 */
int buildHistoryList(info_t *info, char *buf, int linecount)
{
	list_of_items *node = NULL;

	if (info->history)
		node = info->history;
	add_end_node(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumberHistoryEntries - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new historycounter
 */
int renumberHistoryEntries(info_t *info)
{
	list_of_items *node = info->history;
	int n = 0;

	while (node)
	{
		node->num = n++;
		node = node->next;
	}
	return (info->historycounter = n);
}
