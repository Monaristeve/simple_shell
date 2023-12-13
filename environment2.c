#include "my_shell.h"

/**
 * duplicate_info - Duplicates environment variable information.
 * @name: The name part of the environment variable.
 * @value: The value part of the environment variable.
 *
 * Return: The duplicated environment variable.
 */
char *duplicate_info(char *name, char *value)
{
	char *new_var;
	int len_name, len_value, total_len;

	len_name = _strlen(name);
	len_value = _strlen(value);
	total_len = len_name + len_value + 2;

	new_var = malloc(sizeof(char) * (total_len));
	_strcpy(new_var, name);
	_strcat(new_var, "=");
	_strcat(new_var, value);
	_strcat(new_var, "\0");

	return (new_var);
}

/**
 * update_environment - Updates the value of an environment variable.
 * @name: The name of the environment variable.
 * @value: The new value of the environment variable.
 * @shell_data: Pointer to the data_shell structure.
 */
void update_environment(char *name, char *value,data_shell *shell_data)
{
	int x;
	char *current_var, *current_name;

	for (x = 0; _environ[x]; x++)
	{
		current_var = _strdup(_environ[x]);
		current_name = _strtok(current_var, "=");

		if (_strcmp(current_name, name) == 0)
		{
			free(_environ[x]);
			_environ[x] = duplicate_info(current_name, value);
			free(current_var);

			return;
		}
		free(current_var);
	}

	_environ = _reallocdp(_environ, x, sizeof(char *) * (x + 2));
	_environ[x] = duplicate_info(name, value);
	_environ[x + 1] = NULL;
}

/**
 * _set_environment - Sets or updates an environment variable.
 * @shell_data: Pointer to the data_shell structure.
 *
 * Return: Always returns 1.
 */
int _set_environment(data_shell *shell_data)
{
	if (shell_data->args[1] == NULL || shell_data->args[2] == NULL)
	{
		get_error(shell_data, -1);
		return (1);
	}

	update_environment(shell_data->args[1], shell_data->args[2], shell_data);

	return (1);
}

/**
 * _unset_environment - Unsets an environment variable.
 * @shell_data: Pointer to the data_shell structure.
 *
 * Return: Always returns 1.
 */
int _unset_environment(data_shell *shell_data)
{
	char **realloc_environ;
	char *current_var, *current_name;
	int x, y, position;

	if (shell_data->args[1] == NULL)
	{
		get_error(shell_data, -1);
		return (1);
	}

	position = -1;

	for (x = 0; _environ[x]; x++)
	{
		current_var = _strdup(_environ[x]);
		current_name = _strtok(current_var, "=");

		if (_strcmp(current_name, shell_data->args[1]) == 0)
		{
			position = x;
		}

		free(current_var);
	}
	if (position == -1)
	{
		get_error(shell_data, -1);
		return (1);
	}

	realloc_environ = malloc(sizeof(char *) * (x));

	for (x = y = 0; _environ[x]; x++)
	{
		if (x != position)
		{
			realloc_environ[y] = _environ[x];
			y++;
		}
	}

	realloc_environ[y] = NULL;
	free(_environ[position]);
	free(_environ);

	_environ = realloc_environ;
	return (1);
}

