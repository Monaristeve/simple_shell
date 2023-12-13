#include "my_shell.h"

/**
 * custom_strcat - Concatenates two strings
 * @destination: Destination string
 * @source: Source string
 * Return: Pointer to the resulting string (destination)
 */
char *custom_strcat(char *destination, const char *source)
{
	int dest_index, src_index;

	for (dest_index = 0; destination[dest_index] != '\0'; dest_index++)
		;

	for (src_index = 0; source[src_index] != '\0'; src_index++)
	{
		destination[dest_index] = source[src_index];
		dest_index++;
	}

	destination[dest_index] = '\0';
	return (destination);
}

/**
 * custom_strcpy - Copies a string
 * @destination: Destination string
 * @source: Source string
 * Return: Pointer to the resulting string (destination)
 */
char *custom_strcpy(char *destination, char *source)
{
	size_t dest_index;

	for (dest_index = 0; source[dest_index] != '\0'; dest_index++)
	{
		destination[dest_index] = source[dest_index];
	}
	destination[dest_index] = '\0';

	return (destination);
}

/**
 * custom_strcmp - Compares two strings
 * @str1: First string
 * @str2: Second string
 * Return: Difference between the first differing characters
 */
int custom_strcmp(char *str1, char *str2)
{
	int index;

	for (index = 0; str1[index] == str2[index] && str1[index]; index++)
		;

	if (str1[index] > str2[index])
		return (1);
	if (str1[index] < str2[index])
		return (-1);
	return (0);
}

/**
 * custom_strchr - Locates a character in a string
 * @str: String to search
 * @character: Character to find
 * Return: Pointer to the first occurrence of character in str, or NULL if not found
 */
char *custom_strchr(char *str, char character)
{
	unsigned int index = 0;

	for (; *(str + index) != '\0'; index++)
		if (*(str + index) == character)
			return (str + index);

	if (*(str + index) == character)
		return (str + index);

	return ('\0');
}

/**
 * custom_strspn - Gets the length of a prefix substring
 * @str: String to check
 * @accept: Characters to include in the prefix
 * Return: Number of bytes in the initial segment of str that consist only
 * of bytes from accept
 */
int custom_strspn(char *str, char *accept)
{
	int str_index, accept_index, is_included;

	for (str_index = 0; *(str + str_index) != '\0'; str_index++)
	{
		is_included = 1;

		for (accept_index = 0; *(accept + accept_index) != '\0'; accept_index++)
		{
			if (*(str + str_index) == *(accept + accept_index))
			{
				is_included = 0;
				break;
			}
		}

		if (is_included == 1)
			break;
	}

	return (str_index);
}

