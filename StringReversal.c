#include "shell.h"

/**
 * reverseString - Reverses a string.
 * @s: The input string to be reversed.
 * Return: void
 */
void reverseString(char *s)
{
int length = 0, x, y;
char *str, temp;

while (length >= 0)
{
if (s[length] == '\0')
break;
length++;
}
str = s;

for (x = 0; x < (length - 1); x++)
{
for (y = x + 1; y > 0; y--)
{
temp = *(str + y);
*(str + y) = *(str + (y - 1));
*(str + (y - 1)) = temp;
}
}
}
