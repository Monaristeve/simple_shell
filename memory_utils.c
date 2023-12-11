#include "shell.h"

/**
 * copyMemory - Copies memory from one location to another
 * @destination: Destination pointer
 * @source: Source pointer
 * @size: Number of bytes to copy
 *
 * Return: None
 */
void copyMemory(void *destination, const void *source, unsigned int size)
{
	char *destPtr = (char *)destination;
	const char *sourcePtr = (const char *)source;
	unsigned int i;

	for (i = 0; i < size; i++)
		destPtr[i] = sourcePtr[i];
}

/**
 * customRealloc - Resizes the memory block
 * @ptr: Pointer to the memory block
 * @oldSize: Old size of the memory block
 * @newSize: New size of the memory block
 *
 * Return: Pointer to the resized memory block
 */
void *customRealloc(void *ptr, unsigned int oldSize, unsigned int newSize)
{
	void *newPtr;

	if (ptr == NULL)
		return (malloc(newSize));

	if (newSize == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (newSize == oldSize)
		return (ptr);

	newPtr = malloc(newSize);
	if (newPtr == NULL)
		return (NULL);

	if (newSize < oldSize)
		copyMemory(newPtr, ptr, newSize);
	else
		copyMemory(newPtr, ptr, oldSize);

	free(ptr);
	return (newPtr);
}

/**
 * customReallocDoublePointer - Resizes an array of strings
 * @ptr: Pointer to the array of strings
 * @oldSize: Old size of the array
 * @newSize: New size of the array
 *
 * Return: Pointer to the resized array of strings
 */
char **customReallocDoublePointer(char **ptr, unsigned int oldSize, unsigned int newSize)
{
	char **newPtr;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * newSize));

	if (newSize == oldSize)
		return (ptr);

	newPtr = malloc(sizeof(char *) * newSize);
	if (newPtr == NULL)
		return (NULL);

	for (i = 0; i < oldSize; i++)
		newPtr[i] = ptr[i];

	free(ptr);

	return (newPtr);
}

