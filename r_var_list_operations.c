#include "shell.h"

/**
 * add_rvar_node -Adds a new node to the r_var list.
 * @head:Pointer to the head of the r_var list.
 * @x:Length of the variable.
 * @val:Value of the variable.
 * @y:Length of the value.
 * Return:Pointer to the updated head of the r_var list.
 */
r_var *add_rvar_node(r_var **head, int x, char *val, int y)
{
	r_var *new, *temp;

	new = malloc(sizeof(r_var));
	if (new == NULL)
		return (NULL);

	new->len_var = x;
	new->val = val;
	new->len_val = y;

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
 * free_rvar_list -Frees the memory allocated for the r_var list.
 * @head:Pointer to the head of the r_var list.
 * Return:None.
 */
void free_rvar_list(r_var **head)
{
	r_var *temp;
	r_var *curr;

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

