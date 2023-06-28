#include "phiros.h"
/**
 * pr_cd_dot - changes to the parent directory
 * @dsh: data relevant (environ)
 * Return: no return
 */
void pr_cd_dot(phiros_shell *dsh)
{
	char pwd[PATH_MAX];
	char *d, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = pr_strdup(pwd);
	pr_set_env("OLDPWD", cp_pwd, dsh);
	d = dsh->args[1];
	if (pr_strcmp(".", d) == 0)
	{
		pr_set_env("PWD", cp_pwd, dsh);
		free(cp_pwd);
		return;
	}
	if (pr_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	pr_rev_string(cp_strtok_pwd);
	cp_strtok_pwd = pr_strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = pr_strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			pr_rev_string(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		pr_set_env("PWD", cp_strtok_pwd, dsh);
	}
	else
	{
		chdir("/");
		pr_set_env("PWD", "/", dsh);
	}
	dsh->status = 0;
	free(cp_pwd);
}

/**
 * pr_cd_to - changes to a dir given by user
 * @dsh: data relevant (directories)
 * Return: no return
 */
void pr_cd_to(phiros_shell *dsh)
{
	char pwd[PATH_MAX];
	char *d, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	d = dsh->args[1];
	if (chdir(d) == -1)
	{
		pr_get_error(dsh, 2);
		return;
	}

	cp_pwd = pr_strdup(pwd);
	pr_set_env("OLDPWD", cp_pwd, dsh);

	cp_dir = pr_strdup(d);
	pr_set_env("PWD", cp_dir, dsh);

	free(cp_pwd);
	free(cp_dir);

	dsh->status = 0;

	chdir(d);
}
/**
 * pr_cd_previous - changes to the previous directory
 * @dsh: data relevant (environ)
 * Return: no return
 */
void pr_cd_previous(phiros_shell *dsh)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = pr_strdup(pwd);

	p_oldpwd = pr_getenv("OLDPWD", dsh->_environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = pr_strdup(p_oldpwd);

	pr_set_env("OLDPWD", cp_pwd, dsh);

	if (chdir(cp_oldpwd) == -1)
		pr_set_env("PWD", cp_pwd, dsh);
	else
		pr_set_env("PWD", cp_oldpwd, dsh);

	p_pwd = pr_getenv("PWD", dsh->_environ);

	write(STDOUT_FILENO, p_pwd, pr_strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	dsh->status = 0;

	chdir(p_pwd);
}

/**
 * pr_cd_to_home - changes to home directory
 * @dsh: data relevant (environ)
 * Return: no return
 */
void pr_cd_to_home(phiros_shell *dsh)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = pr_strdup(pwd);

	home = pr_getenv("HOME", dsh->_environ);

	if (home == NULL)
	{
		pr_set_env("OLDPWD", p_pwd, dsh);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		pr_get_error(dsh, 2);
		free(p_pwd);
		return;
	}

	pr_set_env("OLDPWD", p_pwd, dsh);
	pr_set_env("PWD", home, dsh);
	free(p_pwd);
	dsh->status = 0;
}
