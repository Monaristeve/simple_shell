#include "shell.h"

/**
 * exec_line - Execute a line of input in the shell.
 *
 * @datash: Pointer to the data_shell structure.
 * Return: Return value.
 */
int exec_line(data_shell *datash)
{
	int (*builtin)(data_shell *datash);

	if (datash->args[0] == NULL)
		return (1);

	builtin = get_builtin(datash->args[0]);

	if (builtin != NULL)
		return (builtin(datash));

	return (cmd_exec(datash));
}
