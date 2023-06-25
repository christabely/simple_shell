#include "proshell.h"
/**
 * myhp_env - information for help
 * Return: NULL
 */
void myhp_env(void)
{
	char *hp = "env: env [option] [nm=val] [command [args]]\n\t";

	write(STDOUT_FILENO, hp, christylen(hp));
	hp = "Show shell enviroment.\n";
	write(STDOUT_FILENO, hp, christylen(hp));
}
/**
 * myhp_setenv - for info
 *
 * Return: NULL
 */
void myhp_setenv(void)
{
	char *hp = "setenv: setenv (const char *nm, const char *val,";

	write(STDOUT_FILENO, hp, christylen(hp));
	hp = "int replace)\n\t";
	write(STDOUT_FILENO, hp, christylen(hp));
	hp = "Adds new definition to environment\n";
	write(STDOUT_FILENO, hp, christylen(hp));
}
/**
 * myhp_unsetev - for info
 *
 * Return: NULL
 */
void myhp_unsetenv(void)
{
	char *hp = "unsetenv: unsetenv (const char *nm)\n\t";

	write(STDOUT_FILENO, hp, christylen(hp));
	hp = "clears entry from the environment\n";
	write(STDOUT_FILENO, hp, christylen(hp));
}
/**
 * myhp_gen - For help info
 * Return: NULL
 */
void myhp_gen(void)
{
	char *hp = "^-^ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, hp, christylen(hp));
	hp = "Type 'hp' to access list of internally defined commands";
	write(STDOUT_FILENO, hp, christylen(hp));
	hp = "Type 'hp name hp' to access and learn on the function 'nm'.\n\n ";
	write(STDOUT_FILENO, hp, christylen(hp));
	hp = " sis: sis [nm=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, hp, christylen(hp));
	hp = "[dir]\nexit: exit [n]\n  env: env [option] [nm=val] [command ";
	write(STDOUT_FILENO, hp, christylen(hp));
	hp = "[args]]\n  setenv: setenv [variable] [val]\n  unsetenv: ";
	write(STDOUT_FILENO, hp, christylen(hp));
	hp = "unsetenv [variable]\n";
	write(STDOUT_FILENO, hp, christylen(hp));
}
/**
 * myhp_exit - for help to exit info
 * Return: NULL
 */
void myhp_exit(void)
{
	char *hp = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, hp, christylen(hp));
	hp = "Shell is exited with N status or when omitted";
	write(STDOUT_FILENO, hp, christylen(hp));
	hp = "Status last exited commandis given and executed\n";
	write(STDOUT_FILENO, hp, christylen(hp));
}
