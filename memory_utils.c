#include "shell.h"

/**
 * _memcpy - Copies 'size' bytes from 'ptr' to 'newptr'.
 * @newptr: Destination pointer.
 * @ptr: Source pointer.
 * @size: Number of bytes to copy.
 *
 * Return: None.
 */
void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_newptr = (char *)newptr;
	unsigned int x;

	for (x = 0; x < size; x++)
		char_newptr[x] = char_ptr[x];
}

/**
 * _realloc - Reallocates a memory block.
 * @ptr: Pointer to the previously allocated memory block.
 * @old_size: Size of the old memory block.
 * @new_size: Size of the new memory block.
 *
 * Return: Pointer to the newly allocated memory block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);

	if (new_size < old_size)
		_memcpy(newptr, ptr, new_size);
	else
		_memcpy(newptr, ptr, old_size);

	free(ptr);
	return (newptr);
}

/**
 * _reallocdp - Reallocates a double pointer array.
 * @ptr: Pointer to the old array.
 * @old_size: Size of the old array.
 * @new_size: Size of the new array.
 *
 * Return: Pointer to the newly allocated array.
 */
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newptr;
	unsigned int y;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(sizeof(char *) * new_size);
	if (newptr == NULL)
		return (NULL);

	for (y = 0; y < old_size; y++)
		newptr[y] = ptr[y];

	free(ptr);

	return (newptr);
}

