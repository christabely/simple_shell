#include "proshell.h"

/**
 * idir - checks ":" if is in the current directory.
 * @ph: type char pointer char.
 * @i: type int pointer of index.
 * Return: 1 if the path is searchable in the cd, 0 otherwise.
 */
int idir(char *ph, int *i)
{
	if (pth[*i] == ':')
		return (1);

	while (pth[*i] != ':' && pth[*i])
	{
		*i += 1;
	}

	if (pth[*i])
		*i += 1;

	return (0);
}

/**
 * wh - locates a command
 *
 * @cd: command name
 * @env: environment variable
 * Return: location of the command.
 */
char *wh(char *cd, char **env)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	path = gv("PATH", env);
	if (path)
	{
		ptr_path = christydup(path);
		len_cmd = christylen(cd);
		token_path = christytok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (idir(path, &i))
				if (stat(cd, &st) == 0)
					return (cd);
			len_dir = christylen(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			christycpy(dir, token_path);
			christycat(dir, "/");
			christycat(dir, cd);
			christycat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = christytok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cd, &st) == 0)
			return (cd);
		return (NULL);
	}
	if (cd[0] == '/')
		if (stat(cd, &st) == 0)
			return (cd);
	return (NULL);
}

/**
 * iexec - determines if is an executable
 *
 * @dsh: data structure
 * Return: 0 if is not an executable, other number if it does
 */
int iexec(pro *dsh)
{
	struct stat st;
	int i;
	char *input;

	input = dsh->args[0];
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return (0);
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(input + i, &st) == 0)
	{
		return (i);
	}
	gerror(dsh, 127);
	return (-1);
}

/**
 * cecmd - verifies if user has permissions to access
 *
 * @dr: destination directory
 * @d: data structure
 * Return: 1 if there is an error, 0 if not
 */
int cecmd(char *dr, pro *d)
{
	if (dr == NULL)
	{
		gerror(d, 127);
		return (1);
	}

	if (christycmp(d->args[0], dr) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			gerror(d, 126);
			free(dr);
			return (1);
		}
		free(dr);
	}
	else
	{
		if (access(d->args[0], X_OK) == -1)
		{
			gerror(d, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * cexec - executes command lines
 *
 * @d: data relevant (args and input)
 * Return: 1 on success.
 */
int cexec(pro *d)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;
	(void) wpd;

	exec = iexec(d);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = wh(d->args[0], d->_env);
		if (cecmd(dir, d) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = wh(d->args[0], d->_env);
		else
			dir = d->args[0];
		execve(dir + exec, d->args, d->_env);
	}
	else if (pd < 0)
	{
		perror(d->ar[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	d->status = state / 256;
	return (1);
}

