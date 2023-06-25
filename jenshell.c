#include "proshell.h"
/**
 * sscd - to concatenate error mgs
 * @d: for data
 * @m: to print msgs
 * @error: messages
 * @stv: for string to count lines
 * Return: for error msgs
 */
char *sscd(pro *d, char *m, char *error, char *stv)
{
	char *wrongf;

	christycpy(error, d->ar[0]);
	christycat(error, ": ");
	christycat(error, stv);
	christycat(error, ": ");
	christycat(error, d->args[0]);
	christycat(error, m);
	if (d->args[1][0] == '-')
	{
		wrongf = malloc(3);
		wrongf[0] = '-';
		wrongf[1] = d->args[1][1];
		wrongf[2] = '\0';
		christycat(error, wrongf);
		free(wrongf);
	}
	else
	{
		christycat(error, d->args[1]);
	}
	christycat(error, "\n");
	christycat(error, "\0");
	return (error);
}
/**
 * egd - for error msgs
 * @d: data
 * Return: error msgs
 */
char *egd(pro *d)
{
	int lenght, dl;
	char *error, *stv, *m;

	stv = aitoa(d->count);
	if (d->args[1][0] == '-')
	{
		m = ": wrongo ";
		dl = 2;
	}
	else
	{
		m = ": unable to cd to ";
		dl = christylen(d->args[1]);
	}
	lenght = christylen(d->ar[0]) + christylen(d->args[0]);
	lenght += christylen(stv) + christylen(m) + dl + 5;
	error = malloc(sizeof(char) * (lenght + 1));

	if (error == 0)
	{
		free(stv);
		return (NULL);
	}
	error = sscd(d, m, error, stv);

	free(stv);
	return (error);
}
/**
 * enf - for error msgs
 * @d: for data
 * Return: error sg
 */
char *enf(pro *d)
{
	int lenght;
	char *error;
	char *stv;

	stv = aitoa(d->count);
	lenght = christylen(d->ar[0]) + christylen(stv);
	lenght += christylen(d->args[0]) + 16;
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
	christycat(error, ": unfounded\n");
	christycat(error, "\0");
	free(stv);
	return (error);
}
/**
 * essh - error msg to exit
 * @d: variab data
 * Return: err msgs
 */
char *essh(pro *d)
{
	int lenght;
	char *error;
	char *stv;

	stv = aitoa(d->count);
	lenght = christylen(d->ar[0]) + christylen(stv);
	lenght += christylen(d->args[0]) + christylen(d->args[1]) + 23;
	error = malloc(sizeof(char) * (lenght + 1));
	if (error == 0)
	{
		free(stv);
		return (NULL);
	}
	christycpy(error, d->ar[0]);
	christycat(error, ": ");
	christycat(error, stv);
	christycat(error, ": ");
	christycat(error, d->args[0]);
	christycat(error, ": wrongn: ");
	christycat(error, d->args[1]);
	christycat(error, "\n\0");
	free(stv);
	return (error);
}
