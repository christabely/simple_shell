#include "proshell.h"
/**
 * cj_get_sigint - Handle crtl + c call in prompt
 * @sig: Signal handler
 */
void cj_get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
/**
 * cj_read_line - reads the input string.
 * @iff: return value of getline function
 * Return: input string
 */
char *cj_read_line(int *iff)
{
	char *input = NULL;
	size_t bufsize = 0;

	*iff = getline(&input, &bufsize, stdin);

	return (input);
}
