#include "proshell.h"
/**
 * eline - locates commands and builtin
 * @d: data
 * Return: 1
 */
int eline(pro *d)
{
	int (*b)(pro *d);

	if (d->args[0] == NULL)
		return (1);

	b = gbuilt(d->args[0]);

	if (b != NULL)
		return (b(d));
	return (cmd_e(d));
}
