#include "proshell.h"
/**
 * myhelp - for builtin help info
 * Return: NULL
 */
void myhp(void)
{
	char *hp = "hp: hp [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, hp, christylen(hp));
	hp = "\tAccess and shows builtin commands info.\n ";
	write(STDOUT_FILENO, hp, christylen(hp));
	hp = "Shows builtin commands info.\n";
	write(STDOUT_FILENO, hp, christylen(hp));
}
/**
 * myhp_sis - for info help
 * Return: NULL
 */
void myhp_sis(void)
{
	char *hp = "sis: sis [-p] [nm[=val]...]\n";

	write(STDOUT_FILENO, hp, christylen(hp));
	hp = "\tShows, display sis.\n ";
	write(STDOUT_FILENO, hp, christylen(hp));
}
/**
 * myhp_cd - for info on help
 * Return: NULL
 *
 */
void myhp_cd(void)
{
	char *hp = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, hp, christylen(hp));
	hp = "\tAlters working directory of shell.\n ";
	write(STDOUT_FILENO, hp, christylen(hp));
}
