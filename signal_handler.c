#include "shell.h"

/**
 * signal_interrupt_handler - Handles the SIGINT signal
 * @signal: The signal number
 */
void signal_interrupt_handler(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
