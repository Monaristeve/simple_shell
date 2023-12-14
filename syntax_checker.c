#include "shell.h"

/**
 * count_repeated_chars - Counts the number of repeated characters in a string.
 * @input: The input string.
 * @x: The starting index.
 * Return: The count of repeated characters.
 */
int count_repeated_chars(char *input, int x)
{
	if (*(input - 1) == *input)
		return (count_repeated_chars(input - 1, x + 1));

	return (x);
}

/**
 * error_sep_op - Checks for syntax errors related to separator operators.
 * @input: The input string.
 * @x: The starting index.
 * @last: The last encountered separator operator.
 * Return: The index of the syntax error, if any.
 */
int error_sep_op(char *input, int x, char last)
{
	int count;

	count = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (error_sep_op(input + 1, x + 1, last));

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

	return (error_sep_op(input + 1, x + 1, *input));
}

/**
 * first_char - Finds the index of the first non-space character in a string.
 * @input: The input string.
 * @y: The pointer to store the index.
 * Return: 0 if successful, -1 if a separator operator is found.
 */
int first_char(char *input, int *y)
{
	for (*y = 0; input[*y]; *y += 1)
	{
		if (input[*y] == ' ' || input[*y] == '\t')
			continue;

		if (input[*y] == ';' || input[*y] == '|' || input[*y] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * print_syntax_error - Prints syntax error messages.
 * @datash: The shell data structure.
 * @input: The input string.
 * @x: The index of the syntax error.
 * @bool: A flag indicating whether the error is before or after the operator.
 * Return: None.
 */
void print_syntax_error(data_shell *datash, char *input, int x, int bool __attribute__((unused)))
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	if (input[x] == ';')
	{
		msg = (input[x + 1] == ';' ? ";;" : ";");
	}

	if (input[x] == '|')
		msg = (input[x + 1] == '|' ? "||" : "|");

	if (input[x] == '&')
		msg = (input[x + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\"unexpected\n";
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
 * check_syntax_error - Checks for syntax errors in the input string.
 * @datash: The shell data structure.
 * @input: The input string.
 * Return: 1 if syntax error is found, 0 otherwise.
 */
int check_syntax_error(data_shell *datash, char *input)
{
	int begin = 0;
	int f_char = 0;
	int x = 0;

	f_char = first_char(input, &begin);
	if (f_char == -1)
	{
		print_syntax_error(datash, input, begin, 0);
		return (1);
	}

	x = error_sep_op(input + begin, 0, *(input + begin));
	if (x != 0)
	{
		print_syntax_error(datash, input, begin + x, 1);
		return (1);
	}

	return (0);
}

