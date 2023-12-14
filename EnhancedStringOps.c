#include "shell.h"

/**
 * _strdup - Duplicates a string.
 * @s: The string to duplicate.
 * Return: A pointer to the duplicated string or NULL if memory allocation fails.
 */
char *_strdup(const char *s)
{
char *new;
size_t len;

len = _strlen(s);
new = malloc(sizeof(char) * (len + 1));
if (new == NULL)
return (NULL);
_memcpy(new, s, len + 1);
return (new);
}

/**
 * _strlen - Computes the length of a string.
 * @s: The input string.
 * Return: The length of the string.
 */
int _strlen(const char *s)
{
int len;

for (len = 0; s[len] != 0; len++)
{
}
return (len);
}

/**
 * cmp_chars - Compares characters in a string with a set of delimiters.
 * @str: The input string.
 * @delim: The set of delimiters.
 * Return: 1 if all characters in the string are delimiters, 0 otherwise.
 */
int cmp_chars(char str[], const char *delim)
{
unsigned int x, y, z;

for (x = 0, z = 0; str[x]; x++)
{
for (y = 0; delim[y]; y++)
{
if (str[x] == delim[y])
{
z++;
break;
}
}
}
if (x == z)
return (1);
return (0);
}

/**
 * _strtok - Tokenizes a string based on delimiters.
 * @str: The input string.
 * @delim: The set of delimiters.
 * Return: A pointer to the next token or NULL if no more tokens are found.
 */
char *_strtok(char str[], const char *delim)
{
static char *splitted, *str_end;
char *str_start;
unsigned int x, bool;

if (str != NULL)
{
if (cmp_chars(str, delim))
return (NULL);
splitted = str;
x = _strlen(str);
str_end = &str[x];
}
str_start = splitted;
if (str_start == str_end)
return (NULL);

for (bool = 0; *splitted; splitted++)
{

if (splitted != str_start)
if (*splitted && *(splitted - 1) == '\0')
break;

for (x = 0; delim[x]; x++)
{
if (*splitted == delim[x])
{
*splitted = '\0';
if (splitted == str_start)
str_start++;
break;
}
}
if (bool == 0 && *splitted)
bool = 1;
}
if (bool == 0)
return (NULL);
return (str_start);
}

/**
 * _isdigit - Checks if a string consists of only digit characters.
 * @s: The input string.
 * Return: 1 if the string consists of only digits, 0 otherwise.
 */
int _isdigit(const char *s)
{
unsigned int x;

for (x = 0; s[x]; x++)
{
if (s[x] < 48 || s[x] > 57)
return (0);
}
return (1);
}

