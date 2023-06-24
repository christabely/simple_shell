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
	cpd = christydup(pd);
	senv("OPD", cpd, d);
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

	dir = d->args[1];
	if (chdir(dir) == -1)
	{
		gerror(d, 2);
		return;
	}

	cp_pwd = christydup(pwd);
	senv("OLDPWD", cp_pwd, d);

	cp_dir = christydup(dir);
	senv("PWD", cp_dir, d);

	free(cp_pwd);
	free(cp_dir);

	d->status = 0;

	chdir(dir);
}
/**
 * cdps - changes to the previous directory
 *
 * @d: data relevant (environ)
 * Return: no return
 */
void cdps(pro *d)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = christydup(pwd);

	p_oldpwd = gv("OLDPWD", d->_env);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = christydup(p_oldpwd);

	senv("OLDPWD", cp_pwd, d);

	if (chdir(cp_oldpwd) == -1)
		senv("PWD", cp_pwd, d);
	else
		senv("PWD", cp_oldpwd, d);

	p_pwd = gv("PWD", d->_env);

	write(STDOUT_FILENO, p_pwd, christylen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	d->status = 0;

	chdir(p_pwd);
}

/**
 * cdth - changes to home directory
 *
 * @d: data relevant (environ)
 * Return: no return
 */
void cdth(pro *d)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = christydup(pwd);

	home = gv("HOME", d->_env);

	if (home == NULL)
	{
		senv("OLDPWD", p_pwd, d);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		gerror(d, 2);
		free(p_pwd);
		return;
	}

	senv("OLDPWD", p_pwd, d);
	senv("PWD", home, d);
	free(p_pwd);
	d->status = 0;
}
