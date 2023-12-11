#include "shell.h"

/**
 * reverse_string - Reverses a string in-place
 * @str: The string to reverse
 */
void reverse_string(char *str)
{
	int length = 0, x, y;
	char temp;

	/* Calculate the length of the string */
	while (str[length] != '\0')
	{
		length++;
	}

	/* Reverse the string using a two-pointer approach */
	for (x = 0, y = length - 1; x < y; x++, y--)
	{
		/* Swap characters at positions x and y */
		temp = str[x];
		str[x] = str[y];
		str[y] = temp;
	}
}

