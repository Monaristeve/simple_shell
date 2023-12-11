#include "shell.h"

/**
 * removeComment - Removes comments from a string
 * @input: Input string
 * Return: Modified string without comments or NULL if invalid
 */
char *removeComment(char *input)
{
	int x, upTo;

	upTo = 0;
	for (x = 0; input[x]; x++)
	{
		if (input[x] == '#')
		{
			if (x == 0)
			{
				free(input);
				return (NULL);
			}
			if (input[x - 1] == ' ' || input[x - 1] == '\t' || input[x - 1] == ';')
				upTo = x;
		}
	}

	if (upTo != 0)
	{
		input = customRealloc(input, x, upTo + 1);
		input[upTo] = '\0';
	}

	return (input);
}

/**
 * shellLoop - Main loop for the shell
 * @shellData: Pointer to the shell data structure
 * Return: None
 */
void shellLoop(data_shell *shellData)
{
	int loop, isEof;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = readLine(&isEof);
		if (isEof != -1)
		{
			input = removeComment(input);
			if (input == NULL)
				continue;

			if (checkSyntaxError(shellData, input) == 1)
			{
				shellData->status = 2;
				free(input);
				continue;
			}
			input = replaceVariable(input, shellData);
			loop = splitCommands(shellData, input);
			shellData->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}

