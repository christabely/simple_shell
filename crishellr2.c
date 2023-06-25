#include "proshell.h"
/**
 * christydup - for string duplication
 * @s: pointer
 * Return: string duplicated
 */
char *christydup(const char *s)
{
	char *nw;
	size_t ln;

	ln = christylen(s);
	nw = malloc(sizeof(char) * (ln + 1));
	if (nw == NULL)
		return (NULL);
	shellcpy(nw, s, ln + 1);
	return (nw);
}
/**
 * christylen - for lenght of string
 * @s: pointer
 * Return: Always 0.
 */
int christylen(const char *s)
{
	int ln;

	for (ln = 0; s[ln] != 0; ln++)
	{
	}
	return (ln);
}
/**
 * christychars - compares string chars
 * @s: string
 * @d: deliminator
 * Return: 1 if are equals, 0 if not.
 */
int chirstychars(char s[], const char *d)
{
	unsigned int j, k, l;

	for (j = 0, l = 0; s[j]; j++)
	{
		for (k = 0; d[k]; k++)
		{
			if (s[j] == d[k])
			{
				l++;
				break;
			}
		}
	}
	if (j == l)
		return (1);
	return (0);
}
/**
 * christytok - divides string
 * @s: string
 * @d: delimiter
 * Return: divided string
 */
char *christytok(char s[], const char *d)
{
	static char *sp, *se;
	char *st;
	unsigned int j, bool;

	if (s != NULL)
	{
		if (chirstychars(s, d))
			return (NULL);
		sp = s;
		j = christylen(s);
		se = &s[j];
	}
	st = sp;
	if (st == se)
		return (NULL);

	for (bool = 0; *sp; sp++)
	{
		/*on locating next token split loop*/
		if (sp != st)
			if (*sp && *(sp - 1) == '\0')
				break;
		/*delimiter replacemnt*/
		for (j = 0; d[j]; j++)
		{
			if (*sp == d[j])
			{
				*sp = '\0';
				if (sp == st)
					st++;
				break;
			}
		}
		if (bool == 0 && *sp)
			bool = 1;
	}
	if (bool == 0)
		return (NULL);
	return (st);
}
/**
 * christigit - determines whether string passed is a number
 * @s: string
 * Return: 1 else 0
 */
int christigit(const char *s)
{
	unsigned int j;

	for (j = 0; s[j]; j++)
	{
		if (s[j] < 48 || s[j] > 57)
			return (0);
	}
	return (1);
}
