#include "main.h"

/**
 * str_length - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int str_length(char *s)
{
	int n = 0;

	if (!s)
		return (0);

	while (*s++)
		n++;
	return (n);
}

/**
 * str_compare - performs lexicogarphic comparison of two strangs.
 * @s1: the first strang
 * @s2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int str_compare(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * str_starts_with - checks if target_str starts with search_str
 * @search_str: string to search
 * @target_str: the substring to find
 *
 * Return: address of next char of search_str or NULL
 */
char *str_starts_with(const char *search_str, const char *target_str)
{
	while (*target_str)
		if (*target_str++ != *search_str++)
			return (NULL);
	return ((char *)search_str);
}

/**
 * str_concatenate - concatenates two strings
 * @destination: the destinationination buffer
 * @src_str: the source buffer
 *
 * Return: pointer to destinationination buffer
 */
char *str_concatenate(char *destination, char *src_str)
{
	char *ret = destination;

	while (*destination)
		destination++;
	while (*src_str)
		*destination++ = *src_str++;
	*destination = *src_str;
	return (ret);
}
