#include "proshell.h"
/**
 * rline - reads string input
 * @f: return function value
 * Return: string
 */
char *rline(int *f)
{
	char *log = NULL;
	size_t bufsize = 0;

	*f = getline(&log, &bufsize, stdin);

	return (log);
}
