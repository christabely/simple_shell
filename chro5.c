#include "phiros.h"

/**
 * pr_add_sep_node_end - add up a separator found
 * at the end of a sep_list.
 * @head: head of inked list.
 * @sep: separator found (; | &).
 * Return: address of the head.
 */
sep_list *pr_add_sep_node_end(sep_list **head, char sep)
{
	sep_list *new, *temp;

	new = malloc(sizeof(sep_list));
	if (new == NULL)
		return (NULL);

	new->separator = sep;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * pr_free_sep_list - frees up the a sep_list
 * @head: head of linked list.
 * Return: no return.
 */
void pr_free_sep_list(sep_list **head)
{
	sep_list *temp;
	sep_list *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}

/**
 * pr_add_line_node_end - add up a command line
 * at the end of a line_list.
 * @head: head of linked list.
 * @line: a command line.
 * Return: the address of the head.
 */
line_list *pr_add_line_node_end(line_list **head, char *line)
{
	line_list *new, *temp;

	new = malloc(sizeof(line_list));
	if (new == NULL)
		return (NULL);

	new->line = line;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * pr_free_line_list - frees up a line_list
 * @head: head of linked list.
 * Return: no return.
 */
void pr_free_line_list(line_list **head)
{
	line_list *temp;
	line_list *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}
