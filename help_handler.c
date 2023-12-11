#include "my_shell.h"

/**
 * display_shell_help - Displays help information for shell commands
 * @datash: Pointer to the shell's data structure
 * Return: Always returns 1
 */
int display_shell_help(data_shell *datash)
{
	if (datash->args[1] == NULL)
		show_general_help();
	else if (_strcmp(datash->args[1], "setenv") == 0)
		show_setenv_help();
	else if (_strcmp(datash->args[1], "env") == 0)
		show_env_help();
	else if (_strcmp(datash->args[1], "unsetenv") == 0)
		show_unsetenv_help();
	else if (_strcmp(datash->args[1], "help") == 0)
		show_help();
	else if (_strcmp(datash->args[1], "exit") == 0)
		show_exit_help();
	else if (_strcmp(datash->args[1], "cd") == 0)
		show_cd_help();
	else if (_strcmp(datash->args[1], "alias") == 0)
		show_alias_help();
	else
		write(STDERR_FILENO, datash->args[0], _strlen(datash->args[0]));

	datash->status = 0;
	return (1);
}

