#include "proshell.h"
/**
 * eenv - for error msgs
 * @d: for data
 * Return: error message.
 */
char *eenv(pro *d)
{
	int lenght;
	char *error;
	char *stv;
	char *m;

	stv = aitoa(d->count);
	m = ": inabilit to add/remove from environment\n";
	lenght = christylen(d->ar[0]) + christylen(stv);
	lenght += christylen(d->args[0]) + christylen(m) + 4;
	error = malloc(sizeof(char) * (lenght + 1));
	if (error == 0)
	{
		free(error);
		free(stv);
		return (NULL);
	}
	christycpy(error, d->ar[0]);
	christycat(error, ": ");
	christycat(error, stv);
	christycat(error, ": ");
	christycat(error, d->args[0]);
	christycat(error, m);
	christycat(error, "\0");
	free(stv);
	return (error);
}
/**
 * ep126 - for error msg
 * @d: for data
 * Return: to error
 */
char *ep126(pro *d)
{
	int lenght;
	char *stv;
	char *error;

	stv = aitoa(d->count);
	lenght = christylen(d->ar[0]) + christylen(stv);
	lenght += christylen(d->args[0]) + 24;
	error = malloc(sizeof(char) * (lenght + 1));
	if (error == 0)
	{
		free(error);
		free(stv);
		return (NULL);
	}
	christycpy(error, d->ar[0]);
	christycat(error, ": ");
	christycat(error, stv);
	christycat(error, ": ");
	christycat(error, d->args[0]);
	christycat(error, ": Permission denied\n");
	christycat(error, "\0");
	free(stv);
	return (error);
}
