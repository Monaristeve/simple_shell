#include "shell.h"

/**
 * get_sigint - Handles the SIGINT signal
 * @signal: The signal number
 */
void get_sigint(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
