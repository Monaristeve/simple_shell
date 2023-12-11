#include "shell.h"

/**
 * freeShellData - Frees memory allocated for shell data
 * @shellData: Pointer to the shell data structure
 */
void freeShellData(data_shell *shellData)
{
	unsigned int x;

	for (x = 0; shellData->_environ[x]; x++)
	{
		free(shellData->_environ[x]);
	}

	free(shellData->_environ);
	free(shellData->pid);
}

/**
 * initializeShellData - Initializes the shell data structure
 * @shellData: Pointer to the shell data structure
 * @arguments: Command-line arguments
 */
void initializeShellData(data_shell *shellData, char **arguments)
{
	unsigned int x;

	shellData->arguments = arguments;
	shellData->input = NULL;
	shellData->args = NULL;
	shellData->status = 0;
	shellData->counter = 1;

	for (x = 0; environ[x]; x++)
		;

	shellData->_environ = malloc(sizeof(char *) * (x + 1));

	for (x = 0; environ[x]; x++)
	{
		shellData->_environ[x] = _strdup(environ[x]);
	}

	shellData->_environ[x] = NULL;
	shellData->pid = intToString(getpid());
}

/**
 * main - Entry point for the shell program
 * @argc: Number of command-line arguments
 * @argv: Array of command-line arguments
 * Return: Exit status of the shell
 */
int main(int argc, char **argv)
{
	data_shell shellData;
	(void) argc;

	signal(SIGINT, handleSigint);
	initializeShellData(&shellData, argv);
	shellLoop(&shellData);
	freeShellData(&shellData);

	if (shellData.status < 0)
		return (255);
	return (shellData.status);
}

