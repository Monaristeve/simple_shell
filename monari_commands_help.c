#include "my_shell.h"

/**
 * displayHelp - Displays help information for the 'help' command
 *
 * Return: None
 */
void displayHelp(void)
{
	char *helpMessage = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, helpMessage, _strlen(helpMessage));
	helpMessage = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, helpMessage, _strlen(helpMessage));
	helpMessage = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, helpMessage, _strlen(helpMessage));
}

/**
 * displayAliasHelp - Displays help information for the 'alias' command
 *
 * Return: None
 */
void displayAliasHelp(void)
{
	char *helpMessage = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, helpMessage, _strlen(helpMessage));
	helpMessage = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, helpMessage, _strlen(helpMessage));
}

/**
 * displayCdHelp - Displays help information for the 'cd' command
 *
 * Return: None
 */
void displayCdHelp(void)
{
	char *helpMessage = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, helpMessage, _strlen(helpMessage));
	helpMessage = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, helpMessage, _strlen(helpMessage));
}

