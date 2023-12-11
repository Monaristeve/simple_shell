#include "shell.h"

/**
 * displayEnvHelp - Displays help information for the 'env' command
 *
 * Return: None
 */
void displayEnvHelp(void)
{
	char *helpMessage = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, helpMessage, _strlen(helpMessage));
	helpMessage = "Print the environment of the shell.\n";
	write(STDOUT_FILENO, helpMessage, _strlen(helpMessage));
}

/**
 * displaySetenvHelp - Displays help information for the 'setenv' command
 *
 * Return: None
 */
void displaySetenvHelp(void)
{
	char *helpMessage = "setenv: setenv (const char *name, const char *value, int replace)\n\t";

	write(STDOUT_FILENO, helpMessage, _strlen(helpMessage));
	helpMessage = "Add a new definition to the environment.\n";
	write(STDOUT_FILENO, helpMessage, _strlen(helpMessage));
}

/**
 * displayUnsetenvHelp - Displays help information for the 'unsetenv' command
 *
 * Return: None
 */
void displayUnsetenvHelp(void)
{
	char *helpMessage = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, helpMessage, _strlen(helpMessage));
	helpMessage = "Remove an entry completely from the environment.\n";
	write(STDOUT_FILENO, helpMessage, _strlen(helpMessage));
}

/**
 * displayGeneralHelp - Displays general help information for the shell
 *
 * Return: None
 */
void displayGeneralHelp(void)
{
	char *helpMessage = "^-^ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, helpMessage, _strlen(helpMessage));
	helpMessage = "These commands are defined internally. Type 'help' to see the list.";
	write(STDOUT_FILENO, helpMessage, _strlen(helpMessage));
	helpMessage = "Type 'help name' to find out more about the function 'name'.\n\n ";
	write(STDOUT_FILENO, helpMessage, _strlen(helpMessage));
	helpMessage = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, helpMessage, _strlen(helpMessage));
	helpMessage = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, helpMessage, _strlen(helpMessage));
	helpMessage = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, helpMessage, _strlen(helpMessage));
	helpMessage = "unsetenv [variable]\n";
	write(STDOUT_FILENO, helpMessage, _strlen(helpMessage));
}

/**
 * displayExitHelp - Displays help information for the 'exit' command
 *
 * Return: None
 */
void displayExitHelp(void)
{
	char *helpMessage = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, helpMessage, _strlen(helpMessage));
	helpMessage = "Exits the shell with a status of N. If N is omitted, the exit";
	write(STDOUT_FILENO, helpMessage, _strlen(helpMessage));
	helpMessage = "status is that of the last command executed.\n";
	write(STDOUT_FILENO, helpMessage, _strlen(helpMessage));
}

