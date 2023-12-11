#include "my_shell.h"

/**
 * handle_sigint - Signal handler for SIGINT
 * @signal_number: The signal number
 */
void handle_sigint(int signal_number)
{
	(void)signal_number;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
