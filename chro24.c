#include "phiros.h"
/**
 * pr_get_sigint - Handle crtl + c call in prompt
 * @sig: Signal handler
 */
void pr_get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
/**
 * pr_read_line- reads the input string.
 * @iff: return value of getline function
 * Return: input string
 */
char *pr_read_line(int *iff)
{
	char *input = NULL;
	size_t bufsize = 0;

	*iff = getline(&input, &bufsize, stdin);

	return (input);
}
