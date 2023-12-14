#include "shell.h"

/**
 * get_builtin - Returns the corresponding function pointer for a built-in command.
 * @cmd: The command to look for.
 * Return: Function pointer to the corresponding built-in function, or NULL if not found.
 */
int (*get_builtin(char *cmd))(data_shell *)
{
builtin_t builtin[] = {
{"env", _env},
{"exit", exit_shell},
{"setenv", _setenv},
{"unsetenv", _unsetenv},
{"cd", cd_shell},
{"help", get_help},
{NULL, NULL}
};
int x;

for (x = 0; builtin[x].name; x++)
{
if (_strcmp(builtin[x].name, cmd) == 0)
break;
}
return (builtin[x].f);
}

