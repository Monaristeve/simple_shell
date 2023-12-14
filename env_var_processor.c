#include "shell.h"

/**
 * check_env - Check environment variables and add to the list.
 * @h: Head of the list to store variables.
 * @in: Input string.
 * @data: Shell data.
 * Return: void
 */
void check_env(r_var **h, char *in, data_shell *data)
{
	int row, chr, y, lval;
	char **_envr;

	_envr = data->_environ;
	for (row = 0; _envr[row]; row++)
	{
		for (y = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = _strlen(_envr[row] + chr + 1);
				add_rvar_node(h, y, _envr[row] + chr + 1, lval);
				return;
			}

			if (in[y] == _envr[row][chr])
				y++;
			else
				break;
		}
	}

	for (y = 0; in[y]; y++)
	{
		if (in[y] == ' ' || in[y] == '\t' || in[y] == ';' || in[y] == '\n')
			break;
	}

	add_rvar_node(h, y, NULL, 0);
}

/**
 * check_vars - Check for variables in the input string.
 * @h: Head of the list to store variables.
 * @in: Input string.
 * @st: String to replace.
 * @data: Shell data.
 * Return: Number of characters processed.
 */
int check_vars(r_var **h, char *in, char *st, data_shell *data)
{
	int x, lst, lpd;

	lst = _strlen(st);
	lpd = _strlen(data->pid);

	for (x = 0; in[x]; x++)
	{
		if (in[x] == '$')
		{
			if (in[x + 1] == '?')
				add_rvar_node(h, 2, st, lst), x++;
			else if (in[x + 1] == '$')
				add_rvar_node(h, 2, data->pid, lpd), x++;
			else if (in[x + 1] == '\n' || in[x + 1] == '\0' || in[x + 1] == ' ' || in[x + 1] == '\t' || in[x + 1] == ';')
				add_rvar_node(h, 0, NULL, 0);
			else
				check_env(h, in + x, data);
		}
	}

	return (x);
}

/**
 * replaced_input - Replace variables in the input string.
 * @head: Head of the list containing variables.
 * @input: Original input string.
 * @new_input: New string with replaced variables.
 * @nlen: Length of the new string.
 * Return: Modified input string.
 */
char *replaced_input(r_var **head, char *input, char *new_input, int nlen)
{
	r_var *indx;
	int x, y, z;

	indx = *head;
	for (y = x = 0; x < nlen; x++)
	{
		if (input[y] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new_input[x] = input[y];
				y++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (z = 0; z < indx->len_var; z++)
					y++;
				x--;
			}
			else
			{
				for (z = 0; z < indx->len_val; z++)
				{
					new_input[x] = indx->val[z];
					x++;
				}
				y += (indx->len_var);
				x--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[x] = input[y];
			y++;
		}
	}

	return (new_input);
}

/**
 * rep_var - Replace variables in the input string.
 * @input: Original input string.
 * @datash: Shell data.
 * Return: Modified input string.
 */
char *rep_var(char *input, data_shell *datash)
{
	r_var *head, *indx;
	char *status, *new_input;
	int olen, nlen;

	status = aux_itoa(datash->status);
	head = NULL;

	olen = check_vars(&head, input, status, datash);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = replaced_input(&head, input, new_input, nlen);

	free(input);
	free(status);
	free_rvar_list(&head);

	return (new_input);
}

