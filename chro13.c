#include "proshell.h"
/**
 * cj_cd_shell - changes current directory
 * @dtsh: data relevant
 * Return: 1 on success
 */
int cj_cd_shell(project_shell *dtsh)
{
	char *d;
	int x, y, z;

	d = dtsh->args[1];

	if (d != NULL)
	{
		x = cj_strcmp("$HOME", d);
		y = cj_strcmp("~", d);
		z = cj_strcmp("--", d);
	}

	if (d == NULL || !x || !y || !z)
	{
		cj_cd_to_home(dtsh);
		return (1);
	}

	if (cj_strcmp("-", d) == 0)
	{
		cj_cd_previous(dtsh);
		return (1);
	}

	if (cj_strcmp(".", d) == 0 || cj_strcmp("..", d) == 0)
	{
		cj_cd_dot(dtsh);
		return (1);
	}

	cj_cd_dot(dtsh);

	return (1);
}

