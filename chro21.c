#include "phiros.h"
/**
 * pr_get_error - calls the error according the builtin, syntax or permission
 * @dsh: data structure that contains arguments
 * @eva: error value
 * Return: error
 */
int pr_get_error(phiros_shell *dsh, int eva)
{
	char *e;

	switch (eva)
	{
	case -1:
		e = e_e(dsh);
		break;
	case 126:
		e = e_p_126(dsh);
		break;
	case 127:
		e = e_n_f(dsh);
		break;
	case 2:
		if (pr_strcmp("exit", dsh->args[0]) == 0)
			e = e_e_s(dsh);
		else if (pr_strcmp("cd", dsh->args[0]) == 0)
			e = e_g_cd(dsh);
		break;
	}

	if (e)
	{
		write(STDERR_FILENO, e, pr_strlen(e));
		free(e);
	}

	dsh->status = eva;
	return (eva);
}
