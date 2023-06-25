#include "proshell.h"

/**
 * cinfo - copies info
 * @n: name (env or alias)
 * @val: value (env or alias)
 *
 * Return: new env or alias.
 */
char *cinfo(char *n, char *val)
{
	char *new;
	int len_name, len_value, len;

	len_name = christylen(n);
	len_value = christylen(val);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	christycpy(new, n);
	christycat(new, "=");
	christycat(new, val);
	christycat(new, "\0");

	return (new);
}

/**
 * senv - sets an environment variable
 *
 * @n: name of the environment variable
 * @val: value of the environment variable
 * @d: data structure
 * Return: no return
 */
void senv(char *n, char *val, pro *d)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; d->_environ[i]; i++)
	{
		var_env = christydup(d->_environ[i]);
		name_env = christytok(var_env, "=");
		if (christycmp(name_env, n) == 0)
		{
			free(d->_environ[i]);
			d->_environ[i] = cinfo(name_env, val);
			free(var_env);
			return;
		}
		free(var_env);
	}

	d->_environ = shellocdp(d->_environ, i, sizeof(char *) * (i + 2));
	d->_environ[i] = cinfo(n, val);
	d->_environ[i + 1] = NULL;
}

/**
 * stenv - compares env variables names
 * @d: data relevant (env name and env value)
 *
 * Return: 1 on success.
 */
int stenv(pro *d)
{

	if (d->args[1] == NULL || d->args[2] == NULL)
	{
		gerror(d, -1);
		return (1);
	}

	senv(d->args[1], d->args[2], d);

	return (1);
}

/**
 * setenvv - deletes a environment variable
 * @d: data relevant (env name)
 *
 * Return: 1 on success.
 */
int setenvv(pro *d)
{
	char **r;
	char *var_env, *name_env;
	int i, j, k;

	if (d->args[1] == NULL)
	{
		gerror(d, -1);
		return (1);
	}
	k = -1;
	for (i = 0; d->_environ[i]; i++)
	{
		var_env = christydup(d->_environ[i]);
		name_env = christytok(var_env, "=");
		if (christycmp(name_env, d->args[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		gerror(d, -1);
		return (1);
	}
	r = malloc(sizeof(char *) * (i));
	for (i = j = 0; d->_environ[i]; i++)
	{
		if (i != k)
		{
			r[j] = d->_environ[i];
			j++;
		}
	}
	r[j] = NULL;
	free(d->_environ[k]);
	free(d->_environ);
	d->_environ = r;
	return (1);
}
