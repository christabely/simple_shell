#include "phiros.h"

/**
 * pr_exec_line - finds builtins and commands
 * @dsh: data relevant (args)
 * Return: 1 on success.
 */
int pr_exec_line(phiros_shell *dsh)
{
	int (*builtin)(phiros_shell *dsh);

	if (dsh->args[0] == NULL)
		return (1);

	builtin = pr_get_builtin(dsh->args[0]);

	if (builtin != NULL)
		return (builtin(dsh));

	return (pr_cmd_exec(dsh));
}
