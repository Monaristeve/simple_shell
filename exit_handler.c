#include "my_shell.h"

/**
 * exitShell - Exits the shell with a specified status
 *
 * @shellData: The shell data structure
 * Return: 1 if an error occurred, 0 otherwise
 */
int exitShell(data_shell *shellData)
{
	unsigned int userStatus;
	int isDigit;
	int strLength;
	int isBigNumber;

	if (shellData->args[1] != NULL)
	{
		userStatus = _atoi(shellData->args[1]);
		isDigit = _isdigit(shellData->args[1]);
		strLength = _strlen(shellData->args[1]);
		isBigNumber = userStatus > (unsigned int)INT_MAX;

		if (!isDigit || strLength > 10 || isBigNumber)
		{
			getError(shellData, 2);
			shellData->status = 2;
			return (1);
		}

		shellData->status = (userStatus % 256);
	}

	return (0);
}

