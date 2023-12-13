#include "my_shell.h"

/**
 * customCdDot - Change directory to '.'.
 * @datash: Shell data structure.
 * Return: None.
 */
void customCdDot(CustomShellData *datash)
{
	char currentDir[PATH_MAX];
	char *directory, *copyPwd, *tokenizedPwd;

	getcwd(currentDir, sizeof(currentDir));
	copyPwd = _strdup(currentDir);
	setEnvironmentVariable("OLDPWD", copyPwd, datash);
	directory = datash->arguments[1];

	if (_customStrcmp(".", directory) == 0)
	{
		setEnvironmentVariable("PWD", copyPwd, datash);
		free(copyPwd);
		return;
	}

	if (_customStrcmp("/", copyPwd) == 0)
	{
		free(copyPwd);
		return;
	}

	tokenizedPwd = copyPwd;
	reverseString(tokenizedPwd);
	tokenizedPwd = _customStrtok(tokenizedPwd, "/");

	if (tokenizedPwd != NULL)
	{
		tokenizedPwd = _customStrtok(NULL, "\0");

		if (tokenizedPwd != NULL)
			reverseString(tokenizedPwd);
	}

	if (tokenizedPwd != NULL)
	{
		chdir(tokenizedPwd);
		setEnvironmentVariable("PWD", tokenizedPwd, datash);
	}
	else
	{
		chdir("/");
		setEnvironmentVariable("PWD", "/", datash);
	}

	datash->status = 0;
	free(copyPwd);
}

/**
 * customCdTo - Change directory to specified path.
 * @datash: Shell data structure.
 * Return: None.
 */
void customCdTo(CustomShellData *datash)
{
	char currentDir[PATH_MAX];
	char *directory, *copyPwd, *copyDir;

	getcwd(currentDir, sizeof(currentDir));
	directory = datash->arguments[1];

	if (chdir(directory) == -1)
	{
		reportError(datash, 2);
		return;
	}

	copyPwd = _strdup(currentDir);
	setEnvironmentVariable("OLDPWD", copyPwd, datash);

	copyDir = _strdup(directory);
	setEnvironmentVariable("PWD", copyDir, datash);

	free(copyPwd);
	free(copyDir);
	datash->status = 0;
	chdir(directory);
}

/**
 * customCdPrevious - Change directory to the previous path.
 * @datash: Shell data structure.
 * Return: None.
 */
void customCdPrevious(CustomShellData *datash)
{
	char currentDir[PATH_MAX];
	char *prevPwd, *prevOldPwd, *copyPwd, *copyOldPwd;

	getcwd(currentDir, sizeof(currentDir));
	copyPwd = _strdup(currentDir);
	prevOldPwd = _getEnvironmentVariable("OLDPWD", datash->_environ);

	if (prevOldPwd == NULL)
		copyOldPwd = copyPwd;
	else
		copyOldPwd = _strdup(prevOldPwd);

	setEnvironmentVariable("OLDPWD", copyPwd, datash);

	if (chdir(copyOldPwd) == -1)
		setEnvironmentVariable("PWD", copyPwd, datash);
	else
		setEnvironmentVariable("PWD", copyOldPwd, datash);

	prevPwd = _getEnvironmentVariable("PWD", datash->_environ);

	write(STDOUT_FILENO, prevPwd, _customStrlen(prevPwd));
	write(STDOUT_FILENO, "\n", 1);

	free(copyPwd);
	if (prevOldPwd)
		free(copyOldPwd);

	datash->status = 0;
	chdir(prevPwd);
}

/**
 * customCdToHome - Change directory to the home path.
 * @datash: Shell data structure.
 * Return: None.
 */
void customCdToHome(CustomShellData *datash)
{
	char *copyPwd, *home;
	char currentDir[PATH_MAX];

	getcwd(currentDir, sizeof(currentDir));
	copyPwd = _strdup(currentDir);
	home = _getEnvironmentVariable("HOME", datash->_environ);

	if (home == NULL)
	{
		setEnvironmentVariable("OLDPWD", copyPwd, datash);
		free(copyPwd);
		return;
	}

	if (chdir(home) == -1)
	{
		reportError(datash, 2);
		free(copyPwd);
		return;
	}

	setEnvironmentVariable("OLDPWD", copyPwd, datash);
	setEnvironmentVariable("PWD", home, datash);
	free(copyPwd);
	datash->status = 0;
}

