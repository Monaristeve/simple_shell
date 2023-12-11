#include "custom_shell.h"

/**
 * customCdShell - Change directory based on user input.
 * @datash: Shell data structure.
 * Return: 1 on success, otherwise 0.
 */
int customCdShell(CustomShellData *datash)
{
	char *directory;
	int isHome, isHome2, isDoubleDash;

	directory = datash->arguments[1];

	if (directory != NULL)
	{
		isHome = _customStrcmp("$HOME", directory);
		isHome2 = _customStrcmp("~", directory);
		isDoubleDash = _customStrcmp("--", directory);
	}

	if (directory == NULL || !isHome || !isHome2 || !isDoubleDash)
	{
		customCdToHome(datash);
		return (1);
	}

	if (_customStrcmp("-", directory) == 0)
	{
		customCdPrevious(datash);
		return (1);
	}

	if (_customStrcmp(".", directory) == 0 || _customStrcmp("..", directory) == 0)
	{
		customCdDot(datash);
		return (1);
	}

	customCdTo(datash);

	return (1);
}

