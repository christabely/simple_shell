#include "phiros.h"

/**
 * a_help_env - Help info for builtin env
 * Return: no return
 */
void a_help_env(void)
{
	char *help = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, help, pr_strlen(help));
	help = "Print the enviroment of the shell.\n";
	write(STDOUT_FILENO, help, pr_strlen(help));

}
/**
 * a_help_setenv - Help info for builtin setenv
 * Return: no return
 */
void a_help_setenv(void)
{

	char *help = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, help, pr_strlen(help));
	help = "int replace)\n\t";
	write(STDOUT_FILENO, help, pr_strlen(help));
	help = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, help, pr_strlen(help));
}
/**
 * a_help_unsetenv - Help info for builtin unsetenv
 * Return: no return
 */
void a_help_unsetenv(void)
{
	char *help = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, help, pr_strlen(help));
	help = "Remove an entry completely from the environment\n";
	write(STDOUT_FILENO, help, pr_strlen(help));
}


/**
 * a_help_general - Entry point for help info for help builtin
 * Return: no return
 */
void a_help_general(void)
{
	char *help = "^-^ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, help, pr_strlen(help));
	help = "These commands are defined internally.Type 'help' to see the list";
	write(STDOUT_FILENO, help, pr_strlen(help));
	help = "Type 'help name' to find out more about the function 'name'.\n\n ";
	write(STDOUT_FILENO, help, pr_strlen(help));
	help = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, help, pr_strlen(help));
	help = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, help, pr_strlen(help));
	help = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, help, pr_strlen(help));
	help = "unsetenv [variable]\n";
	write(STDOUT_FILENO, help, pr_strlen(help));
}
/**
 * a_help_exit - Help info for builint exit
 * Return: no return
 */
void a_help_exit(void)
{
	char *help = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, help, pr_strlen(help));
	help = "Exits the shell with a status of N. If N is ommited, the exit";
	write(STDOUT_FILENO, help, pr_strlen(help));
	help = "statusis that of the last command executed\n";
	write(STDOUT_FILENO, help, pr_strlen(help));
}
