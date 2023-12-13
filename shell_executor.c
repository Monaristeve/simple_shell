#include "my_shell.h"

/**
 * executeCommandLine - Executes a line of command in the shell
 *
 * @shellData: Pointer to the shell data structure
 * Return: Return value based on the execution result
 */
int executeCommandLine(data_shell *shellData)
{
	int (*builtinFunction)(data_shell *shellData);

	if (shellData->arguments[0] == NULL)
		return (1);

	builtinFunction = getBuiltinFunction(shellData->arguments[0]);

	if (builtinFunction != NULL)
		return (builtinFunction(shellData));

	return (executeShellCommand(shellData));
}
