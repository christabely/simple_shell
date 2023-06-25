#include "proshell.h"
/**
 * cds - changes current directory
 * @d: data
 * Return: 1 on success
 */
int cds(pro *d)
{
	char *rd;
	int th, th2, td;

	rd = d->args[1];

	if (rd != NULL)
	{
		th = christycmp("$HOME", rd);
		th2 = christycmp("~", rd);
		td = christycmp("--", rd);
	}
	if (rd == NULL || !th || !th2 || !td)
	{
		cdth(d);
		return (1);
	}
	if (christycmp("-", rd) == 0)
	{
		cdps(d);
		return (1);
	}
	if (christycmp(".", rd) == 0 || christycmp("..", rd) == 0)
	{
		cddt(d);
		return (1);
	}
	cdto(d);
	return (1);
}
