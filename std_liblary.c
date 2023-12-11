#include "shell.h"

/**
 * get_number_length - Calculates the length of an integer
 * @num: The integer
 * Return: Length of the integer
 */
int get_number_length(int num)
{
	unsigned int n;
	int length = 1;

	if (num < 0)
	{
		length++;
		n = (unsigned int)(num * -1);
	}
	else
	{
		n = (unsigned int)num;
	}

	while (n > 9)
	{
		length++;
		n /= 10;
	}

	return (length);
}

/**
 * itoa_wrapper - Converts an integer to a string
 * @num: The integer to convert
 * Return: The converted string
 */
char *itoa_wrapper(int num)
{
	unsigned int n;
	int length = get_number_length(num);
	char *buffer;

	buffer = malloc(sizeof(char) * (length + 1));
	if (buffer == NULL)
		return (NULL);

	buffer[length] = '\0';

	if (num < 0)
	{
		n = (unsigned int)(num * -1);
		buffer[0] = '-';
	}
	else
	{
		n = (unsigned int)num;
	}

	length--;

	do {
		buffer[length] = (n % 10) + '0';
		n /= 10;
		length--;
	} while (n > 0);

	return (buffer);
}

/**
 * atoi_custom - Converts a string to an integer
 * @str: The string to convert
 * Return: The converted integer
 */
int atoi_custom(char *str)
{
	unsigned int count = 0, size = 0, result = 0, sign = 1, multiplier = 1, x;

	while (str[count] != '\0')
	{
		if (size > 0 && (str[count] < '0' || str[count] > '9'))
			break;

		if (str[count] == '-')
			sign *= -1;

		if ((str[count] >= '0') && (str[count] <= '9'))
		{
			if (size > 0)
				multiplier *= 10;
			size++;
		}
		count++;
	}

	for (x = count - size; x < count; x++)
	{
		result = result + ((str[x] - '0') * multiplier);
		multiplier /= 10;
	}

	return (result * sign);
}

