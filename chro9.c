#include "proshell.h"
/**
 * cj_strcat - concatenates two strings
 * @dest: char pointer to the destination of the copied string
 * @src: const char pointer to the source string
 * Return: dest
 */
char *cj_strcat(char *dest, const char *src)
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
 * cj_strcpy - duplicates the string pointed to by src.
 * @dest: char pointer to the destination of the duplicated string
 * @src: char pointer to the source string
 * Return: dest
 */
char *cj_strcpy(char *dest, char *src)
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
 * cj_strcmp - Function that compares two strings.
 * @s1: string to be compared
 * @s2: string to be compared
 * Return: 0 if the strings are equal, positive value
 * if s1 > s2, negative value if s1 < s2
 */
int cj_strcmp(char *s1, char *s2)
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
 * cj_strchr - locates a character in a string
 * @s: string
 * @c: character
 * Return: pointer to the first occurrence of the character c
 */
char *cj_strchr(char *s, char c)
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
 * cj_strspn - acquires the length of a prefix substring
 * @s: initial segment
 * @accept: accepted bytes
 * Return: number of accepted bytes
 */
int cj_strspn(char *s, char *accept)
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
