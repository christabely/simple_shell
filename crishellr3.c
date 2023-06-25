#include "proshell.h"
/**
 * christystring - for string reversal
 * @d: string
 * Return: NULL
 */
void christystring(char *d)
{
	int c = 0, k, l;
	char *s, tp;

	while (c >= 0)
	{
		if (d[c] == '\0')
			break;
		c++;
	}
	s = d;

	for (k = 0; k < (c - 1); k++)
	{
		for (l = k + 1; k > 0; k--)
		{
			tp = *(s + l);
			*(s + l) = *(s + (l - 1));
			*(s + (l - 1)) = tp;
		}
	}
}
