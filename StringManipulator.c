#include "shell.h"

/**
 * _strcat - Concatenates two strings.
 * @dest: The destination string.
 * @src: The source string.
 * Return: Pointer to the resulting string (dest).
 */
char *_strcat(char *dest, const char *src)
{
int x;
int y;

for (x = 0; dest[x] != '\0'; x++)
;

for (y = 0; src[y] != '\0'; y++)
{
dest[x] = src[y];
x++;
}

dest[x] = '\0';
return (dest);
}

/**
 * _strcpy - Copies a string.
 * @dest: The destination string.
 * @src: The source string.
 * Return: Pointer to the resulting string (dest).
 */
char *_strcpy(char *dest, char *src)
{
size_t z;

for (z = 0; src[z] != '\0'; z++)
{
dest[z] = src[z];
}
dest[z] = '\0';

return (dest);
}

/**
 * _strcmp - Compares two strings.
 * @s1: The first string.
 * @s2: The second string.
 * Return: 0 if strings are equal, positive if s1 > s2, negative if s1 < s2.
 */
int _strcmp(char *s1, char *s2)
{
int x;

for (x = 0; s1[x] == s2[x] && s1[x]; x++)
;

if (s1[x] > s2[x])
return (1);
if (s1[x] < s2[x])
return (-1);
return (0);
}

/**
 * _strchr - Locates a character in a string.
 * @s: The string to search.
 * @c: The character to find.
 * Return: Pointer to the first occurrence of c in s, or NULL if not found.
 */
char *_strchr(char *s, char c)
{
unsigned int x = 0;

for (; *(s + x) != '\0'; x++)
if (*(s + x) == c)
return (s + x);
if (*(s + x) == c)
return (s + x);
return ('\0');
}

/**
 * _strspn - Gets the length of a prefix substring.
 * @s: The string to check.
 * @accept: The characters to include in the prefix.
 * Return: Number of bytes in the initial segment of s that consist of accept.
 */
int _strspn(char *s, char *accept)
{
int x, y, bool;

for (x = 0; *(s + x) != '\0'; x++)
{
bool = 1;
for (y = 0; *(accept + y) != '\0'; y++)
{
if (*(s + x) == *(accept + y))
{
bool = 0;
break;
}
}
if (bool == 1)
break;
}
return (x);
}
