#include "shell.h"

/**
 * exit_shell - Exits the shell with a specified status.
 *
 * @datash: Pointer to the data_shell structure.
 * Return: 0 on success, 1 on failure.
 */
int exit_shell(data_shell *datash)
{
	unsigned int xstatus;
	int is_digit;
	int str_len;
	int big_number;

	if (datash->args[1] != NULL)
	{
		xstatus = _atoi(datash->args[1]);
		is_digit = _isdigit(datash->args[1]);
		str_len = _strlen(datash->args[1]);
		big_number = xstatus > (unsigned int)INT_MAX;
		if (!is_digit || str_len > 10 || big_number)
		{
			get_error(datash, 2);
			datash->status = 2;
			return (1);
		}
		datash->status = (xstatus % 256);
	}
	return (0);
}
