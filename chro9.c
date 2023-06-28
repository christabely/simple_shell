#include "phiros.h"
/**
 * pr_strcat - concatenates two strings
 * @dest: char pointer the dest of the copied string
 * @src: const char pointer the source of string
 * Return: dest
 */
char *pr_strcat(char *dest, const char *src)
{
	int r;
	int m;

	for (r = 0; dest[r] != '\0'; r++)
		;

	for (m = 0; src[m] != '\0'; m++)
	{
		dest[r] = src[m];
		r++;
	}

	dest[r] = '\0';
	return (dest);
}
/**
 * *pr_strcpy - duplicates the string pointed to by src.
 * @dest: Type char pointer the dest of the dulpicated string
 * @src: Type char pointer the source of string
 * Return: dest.
 */
char *pr_strcpy(char *dest, char *src)
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
 * pr_strcmp - Function that compares two strings.
 * @s1: type str compared
 * @s2: type str compared
 * Return: Always 0.
 */
int pr_strcmp(char *s1, char *s2)
{
	int y;

	for (y = 0; s1[y] == s2[y] && s1[y]; y++)
		;

	if (s1[y] > s2[y])
		return (1);
	if (s1[y] < s2[y])
		return (-1);
	return (0);
}
/**
 * pr_strchr - locates a character in a string,
 * @s: string.
 * @c: character.
 * Return: the pointer to the first occurrence of the character c.
 */
char *pr_strchr(char *s, char c)
{
	unsigned int p = 0;

	for (; *(s + p) != '\0'; p++)
		if (*(s + p) == c)
			return (s + p);
	if (*(s + p) == c)
		return (s + p);
	return ('\0');
}
/**
 * pr_strspn - acquires the length of a prefix substring.
 * @s: initial segment.
 * @accept: accepted bytes.
 * Return: number of accepted bytes.
 */
int pr_strspn(char *s, char *accept)
{
	int r, d, bool;

	for (r = 0; *(s + r) != '\0'; r++)
	{
		bool = 1;
		for (d = 0; *(accept + d) != '\0'; d++)
		{
			if (*(s + r) == *(accept + d))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (r);
}
