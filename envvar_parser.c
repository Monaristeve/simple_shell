#include "my_shell.h"

/**
 * check_environment - Checks environment variables in the input string
 * @variable_list: Pointer to the variable list
 * @input_str: Input string to check
 * @shell_data: Pointer to the shell's data structure
 * Return: void
 */
void check_environment(r_var **variable_list, char *input_str, data_shell *shell_data)
{
	int row, chr, y, length_val;
	char **environment;

	environment = shell_data->_environ;
	for (row = 0; environment[row]; row++)
	{
		for (y = 1, chr = 0; environment[row][chr]; chr++)
		{
			if (environment[row][chr] == '=')
			{
				length_val = _strlen(environment[row] + chr + 1);
				add_rvar_node(variable_list, y, environment[row] + chr + 1, length_val);
				return;
			}

			if (input_str[y] == environment[row][chr])
				y++;
			else
				break;
		}
	}

	for (y = 0; input_str[y]; y++)
	{
		if (input_str[y] == ' ' || input_str[y] == '\t' || input_str[y] == ';' || input_str[y] == '\n')
			break;
	}

	add_rvar_node(variable_list, y, NULL, 0);
}

/**
 * check_variables - Checks variables in the input string
 * @variable_list: Pointer to the variable list
 * @input_str: Input string to check
 * @status: Status string
 * @shell_data: Pointer to the shell's data structure
 * Return: The length of the checked variables
 */
int check_variables(r_var **variable_list, char *input_str, char *status, data_shell *shell_data)
{
	int x, length_status, length_pid;

	length_status = _strlen(status);
	length_pid = _strlen(shell_data->pid);

	for (x = 0; input_str[x]; x++)
	{
		if (input_str[x] == '$')
		{
			if (input_str[x + 1] == '?')
				add_rvar_node(variable_list, 2, status, length_status), x++;
			else if (input_str[x + 1] == '$')
				add_rvar_node(variable_list, 2, shell_data->pid, length_pid), x++;
			else if (input_str[x + 1] == '\n' || input_str[x + 1] == '\0' ||
				input_str[x + 1] == ' ' || input_str[x + 1] == '\t' || input_str[x + 1] == ';')
				add_rvar_node(variable_list, 0, NULL, 0);
			else
				check_environment(variable_list, input_str + x, shell_data);
		}
	}

	return (x);
}

/**
 * replace_input - Replaces variables in the input string with their values
 * @variable_list: Pointer to the variable list
 * @input_str: Input string to replace variables in
 * @new_input_str: Buffer to store the new input string
 * @new_length: Length of the new input string
 * Return: The modified input string
 */
char *replace_input(r_var **variable_list, char *input_str, char *new_input_str, int new_length)
{
	r_var *index;
	int i, y, k;

	index = *variable_list;
	for (y = i = 0; i < new_length; i++)
	{
		if (input_str[y] == '$')
		{
			if (!(index->len_var) && !(index->len_val))
			{
				new_input_str[i] = input_str[y];
				y++;
			}
			else if (index->len_var && !(index->len_val))
			{
				for (k = 0; k < index->len_var; k++)
					y++;
				i--;
			}
			else
			{
				for (k = 0; k < index->len_val; k++)
				{
					new_input_str[i] = index->val[k];
					i++;
				}
				y += (index->len_var);
				i--;
			}
			index = index->next;
		}
		else
		{
			new_input_str[i] = input_str[y];
			y++;
		}
	}

	return (new_input_str);
}

/**
 * replace_variables - Replaces variables in the input string with their values
 * @input_str: Input string to replace variables in
 * @shell_data: Pointer to the shell's data structure
 * Return: The modified input string
 */
char *replace_variables(char *input_str, data_shell *shell_data)
{
	r_var *variable_list, *index;
	char *status, *new_input_str;
	int old_length, new_length;

	status = aux_itoa(shell_data->status);
	variable_list = NULL;

	old_length = check_variables(&variable_list, input_str, status, shell_data);

	if (variable_list == NULL)
	{
		free(status);
		return (input_str);
	}

	index = variable_list;
	new_length = 0;

	while (index != NULL)
	{
		new_length += (index->len_val - index->len_var);
		index = index->next;
	}

	new_length += old_length;

	new_input_str = malloc(sizeof(char) * (new_length + 1));
	new_input_str[new_length] = '\0';

	new_input_str = replace_input(&variable_list, input_str, new_input_str, new_length);

	free(input_str);
	free(status);
	free_rvar_list(&variable_list);

	return (new_input_str);
}

