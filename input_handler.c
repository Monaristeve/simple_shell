#include "my_shell.h"

/**
 * customReadLine - Reads a line from the standard input
 *
 * @isEndOfFile: Pointer to an integer flag indicating end-of-file status
 * Return: A dynamically allocated string containing the input line
 */
char *customReadLine(int *isEndOfFile)
{
	char *inputBuffer = NULL;
	size_t bufferSize = 0;

	*isEndOfFile = getline(&inputBuffer, &bufferSize, stdin);
	return (inputBuffer);
}
