#include "shell.h"

/**
 * concatenate_cd_error - Concatenates error message for cd command.
 * @datash: Pointer to data_shell structure.
 * @message: The specific error message.
 * @error_msg: Buffer to store the concatenated error message.
 * @version_str: String representation of the command's version.
 * Return: Pointer to the concatenated error message.
 */
char *concatenate_cd_error(data_shell *datash, char *message, char *error_msg, char *version_str)
{
	char *illegal_flag;

	_strcpy(error_msg, datash->av[0]);
	_strcat(error_msg, ": ");
	_strcat(error_msg, version_str);
	_strcat(error_msg, ": ");
	_strcat(error_msg, datash->args[0]);
	_strcat(error_msg, message);
	if (datash->args[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = datash->args[1][1];
		illegal_flag[2] = '\0';
		_strcat(error_msg, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		_strcat(error_msg, datash->args[1]);
	}

	_strcat(error_msg, "\n");
	_strcat(error_msg, "\0");
	return (error_msg);
}

/**
 * get_cd_error - Generates an error message for the cd command.
 * @datash: Pointer to data_shell structure.
 * Return: Pointer to the generated error message.
 */
char *get_cd_error(data_shell *datash)
{
	int length, len_id;
	char *error_msg, *version_str, *message;

	version_str = aux_itoa(datash->counter);
	if (datash->args[1][0] == '-')
	{
		message = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		message = ": can't cd to ";
		len_id = _strlen(datash->args[1]);
	}

	length = _strlen(datash->av[0]) + _strlen(datash->args[0]);
	length += _strlen(version_str) + _strlen(message) + len_id + 5;
	error_msg = malloc(sizeof(char) * (length + 1));

	if (error_msg == 0)
	{
		free(version_str);
		return (NULL);
	}

	error_msg = concatenate_cd_error(datash, message, error_msg, version_str);

	free(version_str);

	return (error_msg);
}

/**
 * not_found_error - Generates an error message for command not found.
 * @datash: Pointer to data_shell structure.
 * Return: Pointer to the generated error message.
 */
char *not_found_error(data_shell *datash)
{
	int length;
	char *error_msg;
	char *version_str;

	version_str = aux_itoa(datash->counter);
	length = _strlen(datash->av[0]) + _strlen(version_str);
	length += _strlen(datash->args[0]) + 16;
	error_msg = malloc(sizeof(char) * (length + 1));
	if (error_msg == 0)
	{
		free(error_msg);
		free(version_str);
		return (NULL);
	}
	_strcpy(error_msg, datash->av[0]);
	_strcat(error_msg, ": ");
	_strcat(error_msg, version_str);
	_strcat(error_msg, ": ");
	_strcat(error_msg, datash->args[0]);
	_strcat(error_msg, ": not found\n");
	_strcat(error_msg, "\0");
	free(version_str);
	return (error_msg);
}

/**
 * exit_shell_error - Generates an error message for the exit shell command.
 * @datash: Pointer to data_shell structure.
 * Return: Pointer to the generated error message.
 */
char *exit_shell_error(data_shell *datash)
{
	int length;
	char *error_msg;
	char *version_str;

	version_str = aux_itoa(datash->counter);
	length = _strlen(datash->av[0]) + _strlen(version_str);
	length += _strlen(datash->args[0]) + _strlen(datash->args[1]) + 23;
	error_msg = malloc(sizeof(char) * (length + 1));
	if (error_msg == 0)
	{
		free(version_str);
		return (NULL);
	}
	_strcpy(error_msg, datash->av[0]);
	_strcat(error_msg, ": ");
	_strcat(error_msg, version_str);
	_strcat(error_msg, ": ");
	_strcat(error_msg, datash->args[0]);
	_strcat(error_msg, ": Illegal number: ");
	_strcat(error_msg, datash->args[1]);
	_strcat(error_msg, "\n\0");
	free(version_str);

	return (error_msg);
}

