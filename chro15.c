#include "phiros.h"
/**
 * pr_is_cdir - checks ":" if is in the current directory.
 * @path: type char pointer char.
 * @m: type int pointer of index.
 * Return: 1 if the path is searchable in the cd, 0 otherwise.
 */
int pr_is_cdir(char *path, int *m)
{
	if (path[*m] == ':')
		return (1);

	while (path[*m] != ':' && path[*m])
	{
		*m += 1;
	}

	if (path[*m])
		*m += 1;

	return (0);
}
/**
 * pr_which - locates a command
 * @cmd: command name
 * @_environ: environment variable
 * Return: location of the command.
 */
char *pr_which(char *cmd, char **_environ)
{
	char *path, *ptr_path, *token_path, *d;
	int len_dir, len_cmd, u;
	struct stat st;

	path = pr_getenv("PATH", _environ);
	if (path)
	{
		ptr_path = pr_strdup(path);
		len_cmd = pr_strlen(cmd);
		token_path = pr_strtok(ptr_path, ":");
		u = 0;
		while (token_path != NULL)
		{
			if (pr_is_cdir(path, &u))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = pr_strlen(token_path);
			d = malloc(len_dir + len_cmd + 2);
			pr_strcpy(d, token_path);
			pr_strcat(d, "/");
			pr_strcat(d, cmd);
			pr_strcat(d, "\0");
			if (stat(d, &st) == 0)
			{
				free(ptr_path);
				return (d);
			}
			free(d);
			token_path = pr_strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}
/**
 * pr_is_executable - determines if is an executable
 * @dsh: data structure
 * Return: 0 if is not an executable, other number if it does
 */
int pr_is_executable(phiros_shell *dsh)
{
	struct stat st;
	int u;
	char *input;

	input = dsh->args[0];
	for (u = 0; input[u]; u++)
	{
		if (input[u] == '.')
		{
			if (input[u + 1] == '.')
				return (0);
			if (input[u + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[u] == '/' && u != 0)
		{
			if (input[u + 1] == '.')
				continue;
			u++;
			break;
		}
		else
			break;
	}
	if (u == 0)
		return (0);

	if (stat(input + u, &st) == 0)
	{
		return (u);
	}
	pr_get_error(dsh, 127);
	return (-1);
}
/**
 * pr_check_error_cmd - verifies if user has permissions to access
 * @d: destination directory
 * @dsh: data structure
 * Return: 1 if there is an error, 0 if not
 */
int pr_check_error_cmd(char *d, phiros_shell *dsh)
{
	if (d == NULL)
	{
		pr_get_error(dsh, 127);
		return (1);
	}

	if (pr_strcmp(dsh->args[0], d) != 0)
	{
		if (access(d, X_OK) == -1)
		{
			pr_get_error(dsh, 126);
			free(d);
			return (1);
		}
		free(d);
	}
	else
	{
		if (access(dsh->args[0], X_OK) == -1)
		{
			pr_get_error(dsh, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * pr_cmd_exec - executes command lines
 * @dsh: data relevant
 * Return: 1 on success.
 */
int pr_cmd_exec(phiros_shell *dsh)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *d;
	(void) wpd;

	exec = pr_is_executable(dsh);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		d = pr_which(dsh->args[0], dsh->_environ);
		if (pr_check_error_cmd(d, dsh) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			d = pr_which(dsh->args[0], dsh->_environ);
		else
			d = dsh->args[0];
		execve(d + exec, dsh->args, dsh->_environ);
	}
	else if (pd < 0)
	{
		perror(dsh->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	dsh->status = state / 256;
	return (1);
}
