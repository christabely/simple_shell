#include "phiros.h"
/**
 * pr_cmp_env_name - compares env variables names
 * with the name passed.
 * @nenv: name of the environment variable
 * @name: name passed
 * Return: 0 if are not equal. Another value if they are.
 */
int pr_cmp_env_name(const char *nenv, const char *name)
{
	int m;

	for (m = 0; nenv[m] != '='; m++)
	{
		if (nenv[m] != name[m])
		{
			return (0);
		}
	}

	return (m + 1);
}
/**
 * pr_getenv - get an environment variable
 * @name: name of the environment variable
 * @_environ: environment variable
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *pr_getenv(const char *name, char **_environ)
{
	char *ptr_env;
	int n, mov;

	ptr_env = NULL;
	mov = 0;

	for (n = 0; _environ[n]; n++)
	{
		mov = pr_cmp_env_name(_environ[n], name);
		if (mov)
		{
			ptr_env = _environ[n];
			break;
		}
	}

	return (ptr_env + mov);
}
/**
 * pr_env - prints the evironment variables
 * @dsh: data relevant.
 * Return: 1 on success.
 */
int pr_env(phiros_shell *dsh)
{
	int g, h;

	for (g = 0; dsh->_environ[g]; g++)
	{

		for (h = 0; dsh->_environ[g][h]; h++)
			;

		write(STDOUT_FILENO, dsh->_environ[g], h);
		write(STDOUT_FILENO, "\n", 1);
	}
	dsh->status = 0;

	return (1);
}
