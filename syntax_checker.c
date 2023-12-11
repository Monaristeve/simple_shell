#include "my_shell.h"

/**
 * count_repeated_chars - Counts the number of repeated characters.
 * @input: The input string.
 * @x: The current position in the input string.
 * Return: The count of repeated characters.
 */
int count_repeated_chars(char *input, int x)
{
	if (*(input - 1) == *input)
		return (count_repeated_chars(input - 1, x + 1));

	return (x);
}

/**
 * check_separator_error - Checks for syntax errors related to separators.
 * @input: The input string.
 * @x: The current position in the input string.
 * @last: The last separator encountered.
 * Return: The position of the error, or 0 if no error is found.
 */
int check_separator_error(char *input, int x, char last)
{
	int count = 0;

	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (check_separator_error(input + 1, x + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (x);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (x);

		if (last == '|')
		{
			count = count_repeated_chars(input, 0);
			if (count == 0 || count > 1)
				return (x);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (x);

		if (last == '&')
		{
			count = count_repeated_chars(input, 0);
			if (count == 0 || count > 1)
				return (x);
		}
	}

	return (check_separator_error(input + 1, x + 1, *input));
}

/**
 * find_first_char - Finds the first non-whitespace character in the input string.
 * @input: The input string.
 * @x: A pointer to the position in the input string.
 * Return: 0 if a valid character is found, -1 otherwise.
 */
int find_first_char(char *input, int *x)
{
	for (*x = 0; input[*x]; *x += 1)
	{
		if (input[*x] == ' ' || input[*x] == '\t')
			continue;

		if (input[*x] == ';' || input[*x] == '|' || input[*x] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * print_syntax_error_msg - Prints syntax error message.
 * @datash: The data shell structure.
 * @input: The input string.
 * @x: The position of the error.
 * @is_last: Flag indicating whether the error is at the end.
 */
void print_syntax_error_msg(data_shell *datash, char *input, int x, int is_last)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	if (input[x] == ';')
	{
		msg = (input[x + 1] == ';' ? ";;" : ";");
		if (is_last)
			msg = (input[x - 1] == ';' ? ";;" : ";");
	}

	if (input[x] == '|')
		msg = (input[x + 1] == '|' ? "||" : "|");

	if (input[x] == '&')
		msg = (input[x + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = aux_itoa(datash->counter);
	length = _strlen(datash->av[0]) + _strlen(counter);
	length += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, msg2);
	_strcat(error, msg);
	_strcat(error, msg3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}

/**
 * validate_syntax - Validates the syntax of the input string.
 * @datash: The data shell structure.
 * @input: The input string.
 * Return: 1 if syntax error found, 0 otherwise.
 */
int validate_syntax(data_shell *datash, char *input)
{
	int start_pos = 0;
	int first_char_result = find_first_char(input, &start_pos);

	if (first_char_result == -1)
	{
		print_syntax_error_msg(datash, input, start_pos, 0);
		return (1);
	}

	int error_pos = check_separator_error(input + start_pos, 0, *(input + start_pos));

	if (error_pos != 0)

	{
		print_syntax_error_msg(datash, input, start_pos + error_pos, 1);
		return (1);
	}

	return (0);
}

