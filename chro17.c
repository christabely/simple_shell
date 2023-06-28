#include "proshell.h"
/**
 * cj_copy_info - copies info to create
 * a new env or alias
 * @name: name (env or alias)
 * @value: value (env or alias)
 * Return: new env or alias.
 */
char *cj_copy_info(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = cj_strlen(name);
	len_value = cj_strlen(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	cj_strcpy(new, name);
	cj_strcat(new, "=");
	cj_strcat(new, value);
	cj_strcat(new, "\0");

	return (new);
}

/**
 * cj_set_env - sets an environment variable
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @dtsh: data structure (environ)
 * Return: no return
 */
void cj_set_env(char *name, char *value, project_shell *dtsh)
{
	int z;
	char *var_env, *name_env;

	for (z = 0; dtsh->_environ[z]; z++)
	{
		var_env = cj_strdup(dtsh->_environ[z]);
		name_env = cj_strtok(var_env, "=");
		if (cj_strcmp(name_env, name) == 0)
		{
			free(dtsh->_environ[z]);
			dtsh->_environ[z] = cj_copy_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	dtsh->_environ = cj_reallocdp(dtsh->_environ, z, sizeof(char *) * (z + 2));
	dtsh->_environ[z] = cj_copy_info(name, value);
	dtsh->_environ[z + 1] = NULL;
}

/**
 * cj_setenv - compares env variables names
 * with the name passed.
 * @dtsh: data relevant (env name and env value)
 * Return: 1 on success.
 */
int cj_setenv(project_shell *dtsh)
{

	if (dtsh->args[1] == NULL || dtsh->args[2] == NULL)
	{
		cj_get_error(dtsh, -1);
		return (1);
	}

	cj_set_env(dtsh->args[1], dtsh->args[2], dtsh);

	return (1);
}

/**
 * cj_unsetenv - deletes a environment variable
 * @dtsh: data relevant (env name)
 * Return: 1 on success.
 */
int cj_unsetenv(project_shell *dtsh)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int q, r, s;

	if (dtsh->args[1] == NULL)
	{
		cj_get_error(dtsh, -1);
		return (1);
	}
	s = -1;
	for (q = 0; dtsh->_environ[q]; q++)
	{
		var_env = cj_strdup(dtsh->_environ[q]);
		name_env = cj_strtok(var_env, "=");
		if (cj_strcmp(name_env, dtsh->args[1]) == 0)
		{
			s = q;
		}
		free(var_env);
	}
	if (s == -1)
	{
		cj_get_error(dtsh, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (q));
	for (q = r = 0; dtsh->_environ[q]; q++)
	{
		if (q != s)
		{
			realloc_environ[r] = dtsh->_environ[q];
			r++;
		}
	}
	realloc_environ[r] = NULL;
	free(dtsh->_environ[s]);
	free(dtsh->_environ);
	dtsh->_environ = realloc_environ;
	return (1);
}

