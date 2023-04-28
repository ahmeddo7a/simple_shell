#include "main.h"

/**
 * add_new_node - adds a new node to the start list
 * @head: address of a pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_of_items *add_new_node(list_of_items **head, const char *str, int num)
{
	list_of_items *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_of_items));
	if (!new_head)
		return (NULL);
	_mem_fill((void *)new_head, 0, sizeof(list_of_items));
	new_head->num = num;
	if (str)
	{
		new_head->str = string_duplicate(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_end_node - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_of_items *add_end_node(list_of_items **head, const char *str, int num)
{
	list_of_items *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_of_items));
	if (!new_node)
		return (NULL);
	_mem_fill((void *)new_node, 0, sizeof(list_of_items));
	new_node->num = num;
	if (str)
	{
		new_node->str = string_duplicate(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_mylist_of_strings - prints only the str element of a list_of_items
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_mylist_of_strings(const list_of_items *h)
{
	size_t m = 0;

	while (h)
	{
		_print_string(h->str ? h->str : "(nil)");
		_print_string("\n");
		h = h->next;
		m++;
	}
	return (m);
}

/**
 * del_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int del_node_at_index(list_of_items **head, unsigned int index)
{
	list_of_items *node, *prev_node;
	unsigned int l = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (l == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		l++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_mylist - frees all nodes
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_mylist(list_of_items **head_ptr)
{
	list_of_items *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
