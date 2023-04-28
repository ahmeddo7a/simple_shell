#include "main.h"

/**
 * mem_free - frees a pointer and NULLs the address
 * @ptr: address of the pointer to be freed
 *
 * Return: 1 if freed, otherwise 0.
 */
int mem_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
