#include "proshell.h"
/**
 * shellcpy - for info copies
 * @n: pointer
 * @p: pointer
 * @s: size
 * Return: NULL
 */
void shellcpy(void *n, const void *p, unsigned int s);
{
	char *char_p = (char *)p;
	char *char_n = (char *)n;
	unsigned int j;

	for (j = 0; j < size; j++)
		char_n[j] = char_p[j];
}
/**
 * shelloc - for memory block
 * @p: pointer
 * @os: for size in byte
 * @ns: for new size in byte
 * Return: @ptr else NULL
 */
void *shelloc(void *p, unsigned int os, unsigned int ns);
{
	void *n;

	if (p == NULL)
		return (malloc(ns));

	if (ns == 0)
	{
		free(p);
		return (NULL);
	}
	if (ns == os)
		return (p);

	n = malloc(ns);
	if (n == NULL)
		return (NULL);

	if (ns < os)
		shellcpy(n, p, ns);
	else
		shellcpy(n, p, os);

	free(p);
	return (n);
}
/**
 * shellocdp - reallocates memory
 * @p: dual pointer
 * @os: for size in bytes
 * @ns: for new size in bytes
 * Return: ptr else NULL
 */
char **shellocdp(char **p, unsigned int os, unsigned int ns);
{
	char **n;
	unsigned int j;

	if (p == NULL)
		return (malloc(sizeof(char *) * ns));

	if (ns == os)
		return (p);

	n = malloc(sizeof(char *) * ns);
	if (n == NULL)
		return (NULL);

	for (j = 0; j < os; j++)
		n[j] = p[j];

	free(p);
	return (n);
}
