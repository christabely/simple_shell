#include "proshell.h"
/**
 * christycat - concatenate strings
 * @d: pointer
 * @s: pointer
 * Return: @d
 */
char *christycat(char *d, const char *s);
{
	int k;
	int l;

	for (k = 0; d[k] != '\0'; k++)
		;

	for (l = 0; s[l] != '\0'; l++)
	{
		d[k] = s[l];
		k++;
	}
	d[k] = '\0';
	return (d);
}
/**
 * *christycpy - copies string
 * @d: destination
 * @s: pointer
 * Return: @d
 */
char *christycpy(char *d, char *s);
{
	size_t v;

	for (v = 0; s[v] != '\0'; v++)
	{
		d[v] = s[v];
	}
	d[v] = '\0';

	return (d);
}
/**
 * christycmp - compares strings
 * @s1: string1
 * @s2: string2
 * Return: Always 0.
 */
int christycmp(char *s1, char *s2);
{
	int k;

	for (k = 0; s1[k] == s2[k] && s1[k]; k++)
		;

	if (s1[k] > s2[k])
		return (1);
	if (s1[k] < s2[k])
		return (-1);
	return (0);
}
/**
 * christychr - locate chars
 * @s: string
 * @c: chars
 * Return: @c
 */
char *christychr(char *s, char c);
{
	unsigned int j = 0;

	for (; *(s + j) != '\0'; j++)
		if (*(s + j) == c)
			return (s + j);
	if (*(s + j) == c)
		return (s + j);
	return ('\0');
}
/**
 * christyspn - gets substring lenght
 * @s: string
 * @a: bytes accepted
 * Return: bytes
 */
int christyspn(char *s, char *a);
{
	int k, l, bool;

	for (k = 0; *(s + k) != '\0'; k++)
	{
		bool = 1;
		for (l = 0; *(a + l) != '\0'; l++)
		{
			if (*(s + k) == *(a + l))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (k);
}
