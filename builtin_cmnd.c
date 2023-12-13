#include "my_shell.h"

/**
 * getCustomBuiltin - Retrieves the function pointer for a custom shell builtin
 * * @command: The name of the command.
 * Return: The function pointer corresponding to the command, or NULL
 */
int (*getCustomBuiltin(char *command))(CustomShellData *)
{
	CustomBuiltinMapping customBuiltins[] = {
		{ "env", customEnv },
		{ "exit", customExit },
		{ "setenv", customSetenv },
		{ "unsetenv", customUnsetenv },
		{ "cd", customCd },
		{ "help", customHelp },
		{ NULL, NULL }
	};
	int index;

	for (index = 0; customBuiltins[index].builtinName; index++)
	{
		if (_customStrcmp(customBuiltins[index].builtinName, command) == 0)
			break;
	}
	return (customBuiltins[index].functionPointer);
}

