#include "proshell.h"
/**
 * cddt - changes to parent directory
 * @d: data
 * Return: NULL
 */
void cddt(pro *d)
{
	char pd;
	char *rd, *cpd, *cps;

	getcwd(pd, sizeof(pd));
	cpd = christyup(pd);
	set_env("OPD", cpd, d);
	rd = d->args[1];
	if (christycmp(".", rd) == 0)
	{
		set_env("PD", cpd, d);
		free(cpd);
		return;
	}
	if (christycmp("/", cpd) == 0)
	{
		free(cpd);
		return;
	}
	cps = cpd;
	christystring(cps);
	cps = christytok(cpd, "/");
	if (cpd != NULL)
	{
		cpd = christytok(NULL, "\0");

		if (cpd != NULL)
			christystring(cpd);
	}
	if (cpd != NULL)
	{
		chdir(cpd);
		senv("PWD", cps, d);
	}
	else
	{
		chdir("/");
		senv("PWD", "/", d);
	}
	d->status = 0;
	free(cpd);
}
/**
 * cdto - changes directory
 * @d: data
 * Return: NULL
 */
void cdto(pro *d)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = datash->args[1];
	if (chdir(dir) == -1)
	{
		get_error(datash, 2);
		return;
	}

	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, datash);

	cp_dir = _strdup(dir);
	set_env("PWD", cp_dir, datash);

	free(cp_pwd);
	free(cp_dir);

	datash->status = 0;

	chdir(rd);
}
/**
 * cd_previous - changes to the previous directory
 *
 * @datash: data relevant (environ)
 * Return: no return
 */
void cd_previous(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	p_oldpwd = _getenv("OLDPWD", datash->_environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);

	set_env("OLDPWD", cp_pwd, datash);

	if (chdir(cp_oldpwd) == -1)
		set_env("PWD", cp_pwd, datash);
	else
		set_env("PWD", cp_oldpwd, datash);

	p_pwd = _getenv("PWD", datash->_environ);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	datash->status = 0;

	chdir(p_pwd);
}

/**
 * cd_to_home - changes to home directory
 *
 * @datash: data relevant (environ)
 * Return: no return
 */
void cd_to_home(data_shell *datash)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	home = _getenv("HOME", datash->_environ);

	if (home == NULL)
	{
		set_env("OLDPWD", p_pwd, datash);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(datash, 2);
		free(p_pwd);
		return;
	}

	set_env("OLDPWD", p_pwd, datash);
	set_env("PWD", home, datash);
	free(p_pwd);
	datash->status = 0;
}
