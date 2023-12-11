#include "my_shell.h"

/**
 * is_command_directory - Checks if the current character is a directory separator
 * @path: The path string
 * @index: Current index in the path string
 * Return: 1 if the current character is a directory separator, 0 otherwise
 */
int is_command_directory(char *path, int *index)
{
	if (path[*index] == ':')
		return (1);

	while (path[*index] != ':' && path[*index])
	{
		*index += 1;
	}

	if (path[*index])
		*index += 1;

	return (0);
}

/**
 * find_executable - Finds the full path of an executable command
 * @cmd: The command to find
 * @environ: The environment variables
 * Return: Full path of the executable command, or NULL if not found
 */
char *find_executable(char *cmd, char **environ)
{
	char *path, *path_ptr, *token_path, *dir;
	int len_dir, len_cmd, index;
	struct stat st;

	path = _getenv("PATH", environ);
	if (path)
	{
		path_ptr = _strdup(path);
		len_cmd = _strlen(cmd);
		token_path = _strtok(path_ptr, ":");
		index = 0;
		while (token_path != NULL)
		{
			if (is_command_directory(path, &index))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = _strlen(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			_strcpy(dir, token_path);
			_strcat(dir, "/");
			_strcat(dir, cmd);
			_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(path_ptr);
				return (dir);
			}
			free(dir);
			token_path = _strtok(NULL, ":");
		}
		free(path_ptr);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * is_command_executable - Checks if the command is executable
 * @datash: The shell data structure
 * Return: The index where the command starts if executable, -1 otherwise
 */
int is_command_executable(data_shell *datash)
{
	struct stat st;
	int index;
	char *input;

	input = datash->args[0];
	for (index = 0; input[index]; index++)
	{
		if (input[index] == '.')
		{
			if (input[index + 1] == '.')
				return (0);
			if (input[index + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[index] == '/' && index != 0)
		{
			if (input[index + 1] == '.')
				continue;
			index++;
			break;
		}
		else
			break;
	}
	if (index == 0)
		return (0);

	if (stat(input + index, &st) == 0)
	{
		return (index);
	}
	get_error(datash, 127);
	return (-1);
}

/**
 * check_command_error - Checks and handles errors for the command
 * @dir: The command directory
 * @datash: The shell data structure
 * Return: 1 if an error occurred, 0 otherwise
 */
int check_command_error(char *dir, data_shell *datash)
{
	if (dir == NULL)
	{
		get_error(datash, 127);
		return (1);
	}

	if (_strcmp(datash->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_error(datash, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(datash->args[0], X_OK) == -1)
		{
			get_error(datash, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * execute_command - Executes the command
 * @datash: The shell data structure
 * Return: 1 on success, 0 on failure
 */
int execute_command(data_shell *datash)
{
	pid_t pid;
	pid_t wpid;
	int status;
	int exec_index;
	char *dir;
	(void) wpid;

	exec_index = is_command_executable(datash);
	if (exec_index == -1)
		return (1);
	if (exec_index == 0)
	{
		dir = find_executable(datash->args[0], datash->_environ);
		if (check_command_error(dir, datash) == 1)
			return (1);
	}

	pid = fork();
	if (pid == 0)
	{
		if (exec_index == 0)
			dir = find_executable(datash->args[0], datash->_environ);
		else
			dir = datash->args[0];
		execve(dir + exec_index, datash->args, datash->_environ);
	}
	else if (pid < 0)
	{
		perror(datash->av[0]);
		return (1);
	}
	else
	{
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	datash->status = status / 256;
	return (1);
}

