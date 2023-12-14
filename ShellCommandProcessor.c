#include "shell.h"

/**
 * without_comment - Removes comments from the input string.
 * @in: The input string.
 * Return: The modified string without comments or NULL on failure.
 */
char *without_comment(char *in)
{
	int x, up_to;

	up_to = 0;
	for (x = 0; in[x]; x++)
	{
		if (in[x] == '#')
		{
			if (x == 0)
			{
				free(in);
				return (NULL);
			}
			if (in[x - 1] == ' ' || in[x - 1] == '\t' || in[x - 1] == ';')
				up_to = x;
		}
	}

	if (up_to != 0)
	{
		in = _realloc(in, x, up_to + 1);
		in[up_to] = '\0';
	}

	return (in);
}

/**
 * shell_loop - Main loop for the shell.
 * @datash: Data structure for the shell.
 * Return: None.
 */
void shell_loop(data_shell *datash)
{
	int loop, x_eof;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = read_line(&x_eof);
		if (x_eof != -1)
		{
			input = without_comment(input);
			if (input == NULL)
				continue;

			if (check_syntax_error(datash, input) == 1)
			{
				datash->status = 2;
				free(input);
				continue;
			}
			input = replace_variable(input, datash);
			loop = split_commands(datash, input);
			datash->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}

