#include "proshell.h"
/**
 * christyenv_nm - for variable compare
 * @nv: variable name
 * @nm: name passed
 * Return: 0 else 1
 */
int christyenv_nm(const char *nv, const char *nm)
{
	int j;

	for (j = 0; nv[j] != '='; j++)
	{
		if (nv[j] != nm[j])
		{
			return (0);
		}
	}
	return (j + 1);
}
/**
 * gv - find environ variable
 * @nm: environ variable name
 * @env: environ variable
 * Return: NULL else number
 */
char *gv(const char *nm, char **env)
{
	char *rv;
	int k, kv;

	rv = NULL;
	kv = 0;

	for (k = 0; env[k]; k++)
	{
		kv = christyenv_nm(env[k], nm);
		if (kv)
		{
			rv = env[k];
			break;
		}
	}
	return (rv + kv);
}
/**
 * env - prints environ variables
 * @d: data
 * Return: 1 on success
 */
int _env(pro *d)
{
	int k, l;

	for (k = 0; d->_environ[k]; k++)
	{
		for (l = 0; d->_environ[k][l]; l++)
			;
		write(STDOUT_FILENO, d->_environ[k], l);
		write(STDOUT_FILENO, "\n", 1);
	}
	d->status = 0;

	return (1);
}
