#include "proshell.h"

/**
 * gbuilt - builtin that pais the command in the arg
 * @c: command
 * Return: function pointer of the builtin command
 */
int (*gbuilt(char *c))(pro *)
{
	built builtin[] = {
		{ "env", _env },
		{ "exit", eshell },
		{ "setenv", stenv },
		{ "unsetenv", setenvv },
		{ "cd", cds },
		{ "help", ghelp },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; builtin[i].nm; i++)
	{
		if (christycmp(builtin[i].nm, c) == 0)
			break;
	}

	return (builtin[i].g);
}
