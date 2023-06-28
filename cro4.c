#include "proshell.h"

/**
 * cj_help - Help info for builtin help.
 * Return: no return
 */
void cj_help(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, cj_strlen(help));
	help = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, help, cj_strlen(help));
	help = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, help, cj_strlen(help));
}

/**
 * cj_help_alias - Help info for builtin alias.
 * Return: no return
 */
void cj_help_alias(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, cj_strlen(help));
	help = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, help, cj_strlen(help));
}

/**
 * cj_help_cd - Help info for builtin cd.
 * Return: no return
 */
void cj_help_cd(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, cj_strlen(help));
	help = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, help, cj_strlen(help));
}
