#include "shell.h"

/**
 * bring_line - Updates lineptr and n based on buffer and j.
 * @lineptr: Pointer to the line buffer.
 * @n: Pointer to the size of the buffer.
 * @buffer: Input buffer.
 * @j: Size of the input buffer.
 */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j)
{
	if (*lineptr == NULL)
	{
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else if (*n < j)
	{
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * get_line - Reads a line from the input stream and updates lineptr and n.
 * @lineptr: Pointer to the line buffer.
 * @n: Pointer to the size of the buffer.
 * @stream: Input stream.
 * Return: The number of characters read, or -1 on failure.
 */
ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
	int x;
	static ssize_t input;
	ssize_t retval;
	char *buffer;
	char t = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		x = read(STDIN_FILENO, &t, 1);
		if (x == -1 || (x == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (x == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buffer = _realloc(buffer, input, input + 1);
		buffer[input] = t;
		input++;
	}
	buffer[input] = '\0';
	bring_line(lineptr, n, buffer, input);
	retval = input;
	if (x != 0)
		input = 0;
	return (retval);
}

