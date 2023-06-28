#include "phiros.h"

/**
 * pr_cd_shell - changes current directory
 * @dsh: data relevant
 * Return: 1 on success
 */
int pr_cd_shell(phiros_shell *dsh)
{
	char *d;
	int ie, i2, ih;

	d = dsh->args[1];

	if (d != NULL)
	{
		ie = pr_strcmp("$HOME", d);
		i2 = pr_strcmp("~", d);
		ih = pr_strcmp("--", d);
	}

	if (d == NULL || !ie || !i2 || !ih)
	{
		pr_cd_to_home(dsh);
		return (1);
	}

	if (pr_strcmp("-", d) == 0)
	{
		pr_cd_previous(dsh);
		return (1);
	}

	if (pr_strcmp(".", d) == 0 || pr_strcmp("..", d) == 0)
	{
		pr_cd_dot(dsh);
		return (1);
	}

	pr_cd_dot(dsh);

	return (1);
}
