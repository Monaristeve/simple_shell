#include "shell.h"

/**
 * cmp_env_name - Compares environment variable name with the given name.
 * @nenv: The environment variable to compare.
 * @name: The name to compare with.
 *
 * Return: Returns 0 if not equal, otherwise the position after the matching part.
 */
int cmp_env_name(const char *nenv, const char *name)
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
 * _getenv - Gets the value of the specified environment variable.
 * @name: The name of the environment variable.
 * @_environ: The environment variables array.
 *
 * Return: Returns the value of the environment variable.
 */
char *_getenv(const char *name, char **_environ)
{
	char *ptr_env;
	int x, mov;

	/* Initialize ptr_env value */
	ptr_env = NULL;
	mov = 0;
	/* Loop through the environment variables */
	for (x = 0; _environ[x]; x++)
	{
		/* Check for a match using cmp_env_name */
		mov = cmp_env_name(_environ[x], name);
		if (mov)
		{
			ptr_env = _environ[x];
			break;
		}
	}

	return (ptr_env + mov);
}

/**
 * _env - Displays all environment variables.
 * @datash: The data structure containing information about the shell.
 *
 * Return: Always returns 1.
 */
int _env(data_shell *datash)
{
	int x, y;

	/* Loop through the environment variables and display them */
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

