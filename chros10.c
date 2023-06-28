#include "phiros.h"
/**
 * pr_strdup - duplicates a str in the heap memory.
 * @s: Type char pointer str
 * Return: duplicated str
 */
char *pr_strdup(const char *s)
{
	char *new;
	size_t len;

	len = pr_strlen(s);
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	_memcpy(new, s, len + 1);
	return (new);
}
/**
 * pr_strlen - Returns the lenght of a string.
 * @s: Type char pointer
 * Return: Always 0.
 */
int pr_strlen(const char *s)
{
	int len;

	for (len = 0; s[len] != 0; len++)
	{
	}
	return (len);
}
/**
 * compare_chars - compare chars of strings
 * @string: input string.
 * @delim: delimiter.
 * Return: 1 if are equals, 0 if not.
 */
int compare_chars(char string[], const char *delim)
{
unsigned int x, y, z;

x = 0;
z = 0;
while (string[x])
{
y = 0;
while (delim[y])
{
if (string[x] == delim[y])
{
z++;
break;
}
y++;
}
x++;
}
if (x == z)
return (1);
return (0);
}
/**
 * pr_strtok - splits a string by some delimiter.
 * @string: input string.
 * @delim: delimiter.
 * Return: string splited.
 */
char *pr_strtok(char string[], const char *delim)
{
static char *split, *string_end;
char *string_start;
unsigned int u, bool;

if (string != NULL)
{
if (compare_chars(string, delim))
return (NULL);
split = string; /*Store first address*/
u = pr_strlen(string);
string_end = &string[u]; /*Store last address*/
}
string_start = split;
if (string_start == string_end) /*Reaching the end*/
return (NULL);

for (bool = 0; *split; split++)
{
/*Breaking loop finding the next token*/
if (split != string_start)
if (*split && *(split - 1) == '\0')
break;
/*Replacing delimiter for null char*/
for (u = 0; delim[u]; u++)
{
if (*split == delim[u])
{
*split = '\0';
if (split == string_start)
string_start++;
break;
}
}
if (bool == 0 && *split) /*String != Delim*/
bool = 1;
}
if (bool == 0) /*String == Delim*/
return (NULL);
return (string_start);
}
/**
 * pr_isdigit - defines if string passed is a number
 * @s: input string
 * Return: 1 if string is a number. 0 in other case.
 */
int pr_isdigit(const char *s)
{
unsigned int u;

u = 0;
while (s[u])
{
if (s[u] < 48 || s[u] > 57)
return (0);
u++;
}
return (1);
}
