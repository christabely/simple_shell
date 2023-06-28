#include "proshell.h"

/**
 * cj_exec_line - finds builtins and commands
 * @dtsh: data relevant (args)
 * Return: 1 on success.
 */
int cj_exec_line(project_shell *dtsh)
{
	int (*builtin)(project_shell *dtsh);

	if (dtsh->args[0] == NULL)
		return (1);

	builtin = cj_get_builtin(dtsh->args[0]);

	if (builtin != NULL)
		return (builtin(dtsh));

	return (cj_cmd_exec(dtsh));
}
