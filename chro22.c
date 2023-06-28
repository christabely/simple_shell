#include "phiros.h"

/**
 * pr_get_help - function that retrieves help messages according builtin
 * @dsh: data structure (args and input)
 * Return: Return 0
*/
int pr_get_help(phiros_shell *dsh)
{

	if (dsh->args[1] == 0)
		a_help_general();
	else if (pr_strcmp(dsh->args[1], "setenv") == 0)
		a_help_setenv();
	else if (pr_strcmp(dsh->args[1], "env") == 0)
		a_help_env();
	else if (pr_strcmp(dsh->args[1], "unsetenv") == 0)
		a_help_unsetenv();
	else if (pr_strcmp(dsh->args[1], "help") == 0)
		a_help();
	else if (pr_strcmp(dsh->args[1], "exit") == 0)
		a_help_exit();
	else if (pr_strcmp(dsh->args[1], "cd") == 0)
		a_help_cd();
	else if (pr_strcmp(dsh->args[1], "alias") == 0)
		a_help_alias();
	else
		write(STDERR_FILENO, dsh->args[0],
		      pr_strlen(dsh->args[0]));

	dsh->status = 0;
	return (1);
}
