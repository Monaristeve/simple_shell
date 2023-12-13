#include "my_shell.h"

/**
 * compare_environment_name - Compares the name of an environment variable.
 * @nenv: The environment variable.
 * @name: The name to compare.
 *
 * Return: The number of matching characters or 0 if not matching.
 */
int compare_environment_name(const char *nenv, const char *name)
{
	int x;

	for (x = 0; nenv[x] != '='; x++)
	{
		if (nenv[x] != name[x])
		{
			return (0);
		}
	}
	return (x + 1);
}

/**
 * get_environment_variable - Retrieves the value of an environment variable.
 * @name: The name of the environment variable.
 * @_environ: The environment variables array.
 *
 * Return: The value of the environment variable or NULL if not found.
 */
char *get_environment_variable(const char *name, char **_environ)
{
	char *variable_ptr;
	int x, move;

	variable_ptr = NULL;
	move = 0;

	for (x = 0; _environ[x]; x++)
	{
		move = compare_environment_name(_environ[x], name);
		if (move)
		{
			variable_ptr = _environ[x];
			break;
		}
	}
	return (variable_ptr + move);
}

/**
 * display_environment - Displays all environment variables.
 *
 * @datash: Pointer to the data_shell structure.
 * Return: Always returns 1.
 */
int display_environment(data_shell *datash)
{
	int x, y;

	for (x = 0; datash->_environ[x]; x++)
	{
		for (y = 0; datash->_environ[x][y]; y++)
			;
		write(STDOUT_FILENO, datash->_environ[x], y);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;
	return (1);
}
