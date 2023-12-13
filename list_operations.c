#include "my_shell.h"

/**
 * add_separator_node_end -  Adds a new node with separator at the end of the list.
 * @separator_list: Pointer to the head of the separator list.
 * @separator: Separator character (; | &).
 * Return: Updated head of the separator list.
 */
sep_list *add_separator_node_end(sep_list **separator_list, char separator)
{
	sep_list *new_separator, *temp;

	new_separator = malloc(sizeof(sep_list));
	if (new_separator == NULL)
		return (NULL);

	new_separator->separator = separator;
	new_separator->next = NULL;
	temp = *separator_list;

	if (temp == NULL)
	{
		*separator_list = new_separator;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_separator;
	}

	return (*separator_list);
}

/**
 * free_separator_list - Frees the memory allocated for the separator list.
 * @separator_list: Pointer to the head of the separator list.
 * Return: void
 */
void free_separator_list(sep_list **separator_list)
{
	sep_list *temp;
	sep_list *current;

	if (separator_list != NULL)
	{
		current = *separator_list;
		while ((temp = current) != NULL)
		{
			current = current->next;
			free(temp);
		}
		*separator_list = NULL;
	}
}

/**
 * add_line_node_end - Adds a new node with line text at the end of the list.
 * @line_list: Pointer to the head of the line list.
 * @line_text: String representing a line.
 * Return: Updated head of the line list.
 */
line_list *add_line_node_end(line_list **line_list, char *line_text)
{
	line_list *new_line, *temp;

	new_line = malloc(sizeof(line_list));
	if (new_line == NULL)
		return (NULL);

	new_line->line = line_text;
	new_line->next = NULL;
	temp = *line_list;

	if (temp == NULL)
	{
		*line_list = new_line;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_line;
	}

	return (*line_list);
}

/**
 * free_line_list - Frees the memory allocated for the line list.
 * @line_list: Pointer to the head of the line list.
 * Return: void
 */
void free_line_list(line_list **line_list)
{
	line_list *temp;
	line_list *current;

	if (line_list != NULL)
	{
		current = *line_list;
		while ((temp = current) != NULL)
		{
			current = current->next;
			free(temp);
		}
		*line_list = NULL;
	}
}

