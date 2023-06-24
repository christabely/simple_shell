#include "proshell.h"
/**
 * cenv - checks for an env variable
 * @h: head of linked lis
 * @in: string
 * @d: data
 * Return: NULL
 */
void cenv(rv **h, char *in, pro *d)
{
	int w, r, i, vv;
	char **en;

	en = d->en;
	for (w = 0; en[w]; w++)
	{
		for (i = 1, r = 0; en[w][r]; r++)
		{
			if (en[w][r] == '=')
			{
				vv = christylen(en[w] + r + 1);
				arvn(h, i, en[w] + r + 1, vv);
				return;
			}
			if (in[i] == en[w][r])
				i++;
			else
				break;
		}
	}
	for (i = 0; in[i]; i++)
	{
		if (in[i] == ' ' || in[i] == '\t' || in[i] == ';' || in[i] == '\n')
			break;
	}
	arvn(h, i, NULL, 0);
}
/**
 * cvars - checks for variable $$ or $?
 * @h: head of linked list
 * @in: string
 * @st: shell last staus
 * @d: data
 * Return: NULL
 */
 int cvars(rv **h, char *in, char *st, pro *d)
{
	int j, ft, ld;

	ft = christylen(st);
	ld = christylen(d->pid);

	for (j = 0; in[j]; j++)
	{
		if (in[j] == '$')
		{
			if (in[j + 1] == '?')
				arvn(h, 2, st, ft), j++;
			else if (in[j + 1] == '$')
				arvn(h, 2, d->pid, ld), j++;
			else if (in[j + 1] == '\n')
				arvn(h, 0, NULL, 0);
			else if (in[j + 1] == '\0')
				arvn(h, 0, NULL, 0);
			else if (in[j + 1] == ' ')
				arvn(h, 0, NULL, 0);
			else if (in[j + 1] == '\t')
				arvn(h, 0, NULL, 0);
			else if (in[j + 1] == ';')
				arvn(h, 0, NULL, 0);
			else
				cenv(h, in + j, d);
		}
	}
	return (i);
}
/**
 * rlogg - replaces string
 * @h: linked list
 * @log: string
 * @nt: new string
 * @nn: new length
 * Return: replaced string
 */
char *rlogg(rv **h, char *log, char *nt, int nn)
{
	rv *indx;
	int l, m, n;

	indx = *h;
	for (m = l = 0; l < nn; l++)
	{
		if (log[m] == '$')
		{
			if (!(indx->lvr) && !(indx->lvl))
			{
				nt[l] = log[j];
				l++;
			}
			else if (indx->lvr && !(indx->lvl))
			{
				for (n = 0; n < indx->lvr; n++)
					m++;
				m--;
			}
			else
			{
				for (n = 0; n < indx->lvl; n++)
				{
					nt[] = indx->val[n];
					l++;
				}
				m += (indx->lvr);
				l--;
			}
			indx = indx->nxt;
		}
		else
		{
			nt[l] = log[m];
			m++;
		}
	}
	return (nt);
}
/**
 * rva - to call functions
 * @log: string
 * @d: data
 * Return: string
 */
char *rva(char *log, pro *d)
{
	rv *u, *ix;
	char *ss, *kt;
	int t, b;

	ss = aitoa(d->ss);
	u = NULL;

	t = cvars(&h, log, ss, d);

	if (u == NULL)
	{
		free(ss);
		return (log);
	}
	ix = u;
	b = 0;

	while (ix != NULL)
	{
		b += (ix->lvl - ix->lvr);
		ix = ix->nxt;
	}
	b += t;

	kt = malloc(sizeof(char) * (b + 1));
	kt[b] = '\0';

	kt = rlogg(&u, log, kt, b);

	free(log);
	free(ss);
	frl(&u);
	return (kt);
}
