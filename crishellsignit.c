#include "proshell.h"
/**
 * gsigint - for handling crtl + c call
 * @sig: handles sig
 */
void gsigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
