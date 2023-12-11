#include "custom_shell.h"

/**
 * updateLine - Updates the line based on the buffer and its length
 * @lineBuffer: Pointer to the line buffer
 * @lineLength: Pointer to the line length
 * @buffer: Buffer containing the input
 * @length: Length of the input buffer
 */
void updateLine(char **lineBuffer, size_t *lineLength, char *buffer, size_t length)
{
	if (*lineBuffer == NULL)
	{
		if (length > BUFSIZE)
			*lineLength = length;
		else
			*lineLength = BUFSIZE;
		*lineBuffer = buffer;
	}
	else if (*lineLength < length)
	{
		if (length > BUFSIZE)
			*lineLength = length;
		else
			*lineLength = BUFSIZE;
		*lineBuffer = buffer;
	}
	else
	{
		_strcpy(*lineBuffer, buffer);
		free(buffer);
	}
}

/**
 * customGetLine - Reads a line from the specified stream
 * @lineBuffer: Pointer to the line buffer
 * @lineLength: Pointer to the line length
 * @stream: File stream to read from
 * Return: The number of bytes read, or -1 on failure
 */
ssize_t customGetLine(char **lineBuffer, size_t *lineLength, FILE *stream)
{
	int bytesRead;
	static ssize_t input;
	ssize_t retrnValue;
	char *buffer;
	char currentChar = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);

	input = 0;
	buffer = malloc(sizeof(char) * BUFSIZE);

	if (buffer == NULL)
		return (-1);

	while (currentChar != '\n')
	{
		bytesRead = read(STDIN_FILENO, &currentChar, 1);

		if (bytesRead == -1 || (bytesRead == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}

		if (bytesRead == 0 && input != 0)
		{
			input++;
			break;
		}

		if (input >= BUFSIZE)
			buffer = _realloc(buffer, input, input + 1);

		buffer[input] = currentChar;
		input++;
	}

	buffer[input] = '\0';
	updateLine(lineBuffer, lineLength, buffer, input);
	retrnValue = input;

	if (bytesRead != 0)
		input = 0;

	return (retrnValue);
}

