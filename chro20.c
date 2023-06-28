#include "phiros.h"

/**
 * pr_get_builtin - builtin that pais the command in the arg
 * @cmd: command
 * Return: function pointer of the builtin command
 */
int (*pr_get_builtin(char *cmd))(phiros_shell *)
{
	builtin_t builtin[] = {
		{ "env", pr_env },
		{ "exit", pr_exit_shell },
		{ "setenv", pr_setenv },
		{ "unsetenv", pr_unsetenv },
		{ "cd", pr_cd_shell },
		{ "help", pr_get_help },
		{ NULL, NULL }
	};
	int u;

	for (u = 0; builtin[u].name; u++)
	{
		if (pr_strcmp(builtin[u].name, cmd) == 0)
			break;
	}

	return (builtin[u].f);
}
