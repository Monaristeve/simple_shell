#include "shell.h"

/**
 * read_line - Reads a line of input from the user.
 *
 * @x_eof: A pointer to an integer to indicate End-of-File status.
 * Return: A dynamically allocated string containing the user input.
 */
char *read_line(int *x_eof)
{
	char *input = NULL;
	size_t bufsize = 0;

	*x_eof = getline(&input, &bufsize, stdin);

	return (input);
}

