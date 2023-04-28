#include "main.h"

/**
 **copy_n_chars - copies a string
 *@destination: the destinationination string to be copied to
 *@src_str: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *copy_n_chars(char *destination, char *src_str, int n)
{
	int k, l;
	char *s = destination;

	k = 0;
	while (src_str[k] != '\0' && k < n - 1)
	{
		destination[k] = src_str[k];
		k++;
	}
	if (k < n)
	{
		l = k;
		while (l < n)
		{
			destination[l] = '\0';
			l++;
		}
	}
	return (s);
}

/**
 **concat_n_chars - concatenates two strings
 *@destination: the first string
 *@src_str: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *concat_n_chars(char *destination, char *src_str, int n)
{
	int i, j;
	char *s = destination;

	i = 0;
	j = 0;
	while (destination[i] != '\0')
		i++;
	while (src_str[j] != '\0' && j < n)
	{
		destination[i] = src_str[j];
		i++;
		j++;
	}
	if (j < n)
		destination[i] = '\0';
	return (s);
}

/**
 **find_char - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *find_char(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
