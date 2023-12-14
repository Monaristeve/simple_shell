#include "shell.h"

/**
 * free_data - Frees memory allocated for data_shell structure.
 * @datash: Pointer to the data_shell structure.
 * Return: void
 */
void free_data(data_shell *datash)
{
	unsigned int x;

	for (x = 0; datash->_environ[x]; x++)
	{
		free(datash->_environ[x]);
	}

	free(datash->_environ);
	free(datash->pid);
}

/**
 * set_data - Initializes data_shell structure with given values.
 * @datash: Pointer to the data_shell structure.
 * @av: Array of strings containing command-line arguments.
 * Return: void
 */
void set_data(data_shell *datash, char **av)
{
	unsigned int x;

	datash->av = av;
	datash->input = NULL;
	datash->args = NULL;
	datash->status = 0;
	datash->counter = 1;

	for (x = 0; environ[x]; x++)
		;

	datash->_environ = malloc(sizeof(char *) * (x + 1));

	for (x = 0; environ[x]; x++)
	{
		datash->_environ[x] = _strdup(environ[x]);
	}

	datash->_environ[x] = NULL;
	datash->pid = aux_itoa(getpid());
}

/**
 * main - Entry point of the program.
 * @ac: Number of command-line arguments.
 * @av: Array of strings containing command-line arguments.
 * Return: Integer representing the exit status.
 */
int main(int ac, char **av)
{
	data_shell datash;
	(void) ac;

	signal(SIGINT, get_sigint);
	set_data(&datash, av);
	shell_loop(&datash);
	free_data(&datash);
	if (datash.status < 0)
		return (255);
	return (datash.status);
}
