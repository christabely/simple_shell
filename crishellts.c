#include "proshell.h"
/**
 * asne - for separators
 * @h: for head
 * @sep: separator (; | &)
 * Return: address
 */
sl *asne(sl **h, char sep)
{
	sl *nw, *tp;

	nw = malloc(sizeof(sl));
	if (nw == NULL)
		return (NULL);

	nw->sep = sep;
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
		tp->nxt = nw;
	}
	return (*h);
}
/**
 * fsl - frees a sep_list
 * @h: linked list head
 * Return: NULL
 */
void fsl(sl **h)
{
	sl *tp, *c;

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
/**
 * alne - adds cmd line
 * @h: linked list h
 * @l: command line
 * Return: to h
 */
ln *alne(ln **h, char *l)
{
	ln *nw, *tp;

	nw = malloc(sizeof(ln));
	if (nw == NULL)
		return (NULL);

	nw->l = l;
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
		tp->nt = nw;
	}
	return (*h);
}
/**
 * fll - frees line_list
 * @h: head
 * Return: NULL
 */
void fll(ln **h)
{
	ln *tp;
	ln *c;

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
