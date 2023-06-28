#include "phiros.h"
/**
 * pr_copy_info - copies info to create
 * a new env or alias
 * @name: name (env or alias)
 * @value: value (env or alias)
 * Return: new env or alias.
 */
char *pr_copy_info(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = pr_strlen(name);
	len_value = pr_strlen(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	pr_strcpy(new, name);
	pr_strcat(new, "=");
	pr_strcat(new, value);
	pr_strcat(new, "\0");

	return (new);
}
/**
 * pr_set_env - sets an environment variable
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @dsh: data structure (environ)
 * Return: no return
 */
void pr_set_env(char *name, char *value, phiros_shell *dsh)
{
	int u;
	char *var_env, *name_env;

	for (u = 0; dsh->_environ[u]; u++)
	{
		var_env = pr_strdup(dsh->_environ[u]);
		name_env = pr_strtok(var_env, "=");
		if (pr_strcmp(name_env, name) == 0)
		{
			free(dsh->_environ[u]);
			dsh->_environ[u] = pr_copy_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	dsh->_environ = pr_reallocdp(dsh->_environ, u, sizeof(char *) * (u + 2));
	dsh->_environ[u] = pr_copy_info(name, value);
	dsh->_environ[u + 1] = NULL;
}

/**
 * pr_setenv - compares env variables names
 * with the name passed.
 * @dsh: data relevant (env name and env value)
 * Return: 1 on success.
 */
int pr_setenv(phiros_shell *dsh)
{

	if (dsh->args[1] == NULL || dsh->args[2] == NULL)
	{
		pr_get_error(dsh, -1);
		return (1);
	}

	pr_set_env(dsh->args[1], dsh->args[2], dsh);

	return (1);
}

/**
 * pr_unsetenv - deletes a environment variable
 * @dsh: data relevant (env name)
 * Return: 1 on success.
 */
int pr_unsetenv(phiros_shell *dsh)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int i, j, k;

	if (dsh->args[1] == NULL)
	{
		pr_get_error(dsh, -1);
		return (1);
	}
	k = -1;
	for (i = 0; dsh->_environ[i]; i++)
	{
		var_env = pr_strdup(dsh->_environ[i]);
		name_env = pr_strtok(var_env, "=");
		if (pr_strcmp(name_env, dsh->args[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		pr_get_error(dsh, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; dsh->_environ[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = dsh->_environ[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(dsh->_environ[k]);
	free(dsh->_environ);
	dsh->_environ = realloc_environ;
	return (1);
}
