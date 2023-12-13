#include "my_shell.h"

/**
 * duplicate_string - Duplicates a string
 * @s: String to duplicate
 * Return: Pointer to the duplicated string
 */
char *duplicate_string(const char *s)
{
	char *duplicate;
	size_t length;

	length = calculate_string_length(s);
	duplicate = malloc(sizeof(char) * (length + 1));
	if (duplicate == NULL)
		return (NULL);
	copy_memory(duplicate, s, length + 1);
	return (duplicate);
}

/**
 * calculate_string_length - Computes the length of a string
 * @s: String to compute the length of
 * Return: Length of the string
 */
int calculate_string_length(const char *s)
{
	int length;

	for (length = 0; s[length] != 0; length++)
	{
	}
	return (length);
}

/**
 * compare_chars - Compares characters in a string with a set of delimiter characters
 * @str: String to compare
 * @delim: Delimiter characters
 * Return: 1 if all characters in the string are delimiters, 0 otherwise
 */
int compare_chars(char str[], const char *delim)
{
	unsigned int x, y, count;

	for (x = 0, count = 0; str[x]; x++)
	{
		for (y = 0; delim[y]; y++)
		{
			if (str[x] == delim[y])
			{
				count++;
				break;
			}
		}
	}
	if (x == count)
		return (1);
	return (0);
}

/**
 * tokenize_string - Tokenizes a string based on a set of delimiters
 * @str: String to tokenize
 * @delim: Delimiter characters
 * Return: Pointer to the next token in the string, or NULL if no more tokens
 */
char *tokenize_string(char str[], const char *delim)
{
	static char *current, *str_end;
	char *token_start;
	unsigned int x, found_token;

	if (str != NULL)
	{
		if (compare_chars(str, delim))
			return (NULL);
		current = str;
		x = calculate_string_length(str);
		str_end = &str[x];
	}
	token_start = current;
	if (token_start == str_end)
		return (NULL);

	for (found_token = 0; *current; current++)
	{
		if (current != token_start)
			if (*current && *(current - 1) == '\0')
				break;

		for (x = 0; delim[x]; x++)
		{
			if (*current == delim[x])
			{
				*current = '\0';
				if (current == token_start)
					token_start++;
				break;
			}
		}
		if (found_token == 0 && *current)
			found_token = 1;
	}
	if (found_token == 0)
		return (NULL);
	return (token_start);
}

/**
 * is_digit_string - Checks if a string consists of digits
 * @s: String to check
 * Return: 1 if the string consists of digits, 0 otherwise
 */
int is_digit_string(const char *s)
{
	unsigned int x;

	for (x = 0; s[x]; x++)
	{
		if (s[x] < '0' || s[x] > '9')
			return (0);
	}
	return (1);
}

