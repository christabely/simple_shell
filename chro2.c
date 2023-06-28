#include "phiros.h"

/**
 * pr_exit_shell - exits the shell
 * @dsh: data relevant (status and args)
 * Return: 0 on success.
 */
int pr_exit_shell(phiros_shell *dsh)
{
	unsigned int us;
	int is_dig;
	int strle_n;
	int big_num;

	if (dsh->args[1] != NULL)
	{
		us = pr_atoi(dsh->args[1]);
		is_dig = pr_isdigit(dsh->args[1]);
		strle_n = pr_strlen(dsh->args[1]);
		big_num = us > (unsigned int)INT_MAX;
		if (!is_dig || strle_n > 10 || big_num)
		{
			pr_get_error(dsh, 2);
			dsh->status = 2;
			return (1);
		}
		dsh->status = (us % 256);
	}
	return (0);
}
