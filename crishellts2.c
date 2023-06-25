#include "proshell.h"
/**
 * arvn - adds variable
 * @h: head of the linked list.
 * @lvr: variable lenght
 * @val: variable value
 * @lvl: value lenght
 * Return: @h
 */
rv *arvn(rv **h, int lvr, char *val, int lvl)
{
	rv *nw, *tp;

	nw = malloc(sizeof(rv));
	if (nw == NULL)
		return (NULL);

	nw->lvr = lvr;
	nw->val = val;
	nw->lvl = lvl;

	nw->nxt = NULL;
	tp = *h;

	if (tp == NULL)
	{
		*h = nw;
	}
	else
	{
		while (tp->nxt != NULL)
			tp = tp->nxt;
		tp->nx = nw;
	}
	return (*h);
}

/**
 * frl - to free a rv list
 * @h: linked list head
 * Return: NULL
 */
void frl(rv **h)
{
	rv *tp;
	rv *c;

	if (h != NULL)
	{
		c = *h;
		while ((tp = c) != NULL)
		{
			c = c->nxt;
			free(tp);
		}
		*h = NULL;
	}
}
