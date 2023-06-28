#include "proshell.h"
/**
 * cj_cmp_env_name - compares env variables names
 * with the name passed.
 * @nenv: name of the environment variable
 * @name: name passed
 * Return: 0 if are not equal. Another value if they are.
 */
int cj_cmp_env_name(const char *nenv, const char *name)
{
	int k;

	for (k = 0; nenv[k] != '='; k++)
	{
		if (nenv[k] != name[k])
		{
			return (0);
		}
	}

	return (k + 1);
}
/**
 * cj_getenv - get an environment variable
 * @name: name of the environment variable
 * @_environ: environment variable
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *cj_getenv(const char *name, char **_environ)
{
	char *ptr_env;
	int z, mov;

	ptr_env = NULL;
	mov = 0;

	for (z = 0; _environ[z]; z++)
	{
		mov = pr_cmp_env_name(_environ[z], name);
		if (mov)
		{
			ptr_env = _environ[z];
			break;
		}
	}

	return (ptr_env + mov);
}
/**
 * cj_env - prints the evironment variables
 * @dtsh: data relevant.
 * Return: 1 on success.
 */
int cj_env(project_shell *dtsh)
{
	int a, b;

	for (a = 0; dtsh->_environ[a]; a++)
	{

		for (b = 0; dtsh->_environ[a][b]; b++)
			;

		write(STDOUT_FILENO, dtsh->_environ[g], b);
		write(STDOUT_FILENO, "\n", 1);
	}
	dtsh->status = 0;

	return (1);
}
