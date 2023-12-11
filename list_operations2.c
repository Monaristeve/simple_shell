#include "shell.h"

/**
 * addReplacementVarNode - Adds a node to the list of replacement variables
 * @head: Pointer to the head of the list
 * @lenVar: Length of the variable name
 * @value: Value of the variable
 * @lenValue: Length of the variable value
 * Return: Pointer to the updated head of the list
 */
r_var *addReplacementVarNode(r_var **head, int lenVar, char *value, int lenValue)
{
	r_var *newNode, *temp;

	newNode = malloc(sizeof(r_var));
	if (newNode == NULL)
		return (NULL);

	newNode->lenVar = lenVar;
	newNode->value = value;
	newNode->lenValue = lenValue;

	newNode->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = newNode;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newNode;
	}

	return (*head);
}

/**
 * freeReplacementVarList - Frees the list of replacement variables
 * @head: Pointer to the head of the list
 */
void freeReplacementVarList(r_var **head)
{
	r_var *temp;
	r_var *current;

	if (head != NULL)
	{
		current = *head;
		while ((temp = current) != NULL)
		{
			current = current->next;
			free(temp);
		}
		*head = NULL;
	}
}

