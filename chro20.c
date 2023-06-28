#include "proshell.h"

/**
 * cj_get_builtin - builtin that pais the command in the arg
 * @cmd: command
 * Return: function pointer of the builtin command
 */
int (*cj_get_builtin(char *cmd))(project_shell *)
{
	builtin_t builtin[] = {
		{ "env", cj_env },
		{ "exit", cj_exit_shell },
		{ "setenv", cj_setenv },
		{ "unsetenv", cj_unsetenv },
		{ "cd", cj_cd_shell },
		{ "help", cj_get_help },
		{ NULL, NULL }
	};
	int v;

	for (v = 0; builtin[v].name; v++)
	{
		if (cj_strcmp(builtin[v].name, cmd) == 0)
			break;
	}

	return (builtin[v].f);
}
