#include "proshell.h"

/**
 * fdata - frees data structure
 *
 * @d: data structure
 * Return: no return
 */
void fdata(pro *d)
{
	unsigned int i;

	for (i = 0; d->_environ[i]; i++)
	{
		free(d->_environ[i]);
	}

	free(d->_environ);
	free(d->pid);
}

/**
 * sdata - Initialize data structure
 *
 * @d: data structure
 * @ar: argument vector
 * Return: no return
 */
void sdata(pro *d, char **ar)
{
	unsigned int i;

	d->ar = ar;
	d->log = NULL;
	d->args = NULL;
	d->status = 0;
	d->count = 1;

	for (i = 0; environ[i]; i++)
		;

	d->_environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		d->_environ[i] = christydup(environ[i]);
	}

	d->_environ[i] = NULL;
	d->pid = aitoa(getpid());
}

/**
 * main - Entry point
 *
 * @ac: argument count
 * @ar: argument vector
 *
 * Return: 0 on success.
 */
int main(int ac, char **ar)
{
	pro d;
	(void) ac;

	signal(SIGINT, gsigint);
	sdata(&d, ar);
	slll(&d);
	fdata(&d);
	if (d.status < 0)
		return (255);
	return (d.status);
}
