#include "phiros.h"
/**
 * pr_strcat_cd - concatenates the msg for cd error
 * @dsh: data relevant (directory)
 * @msg: message to print
 * @e: output message
 * @v_s: counter lines
 * Return: error message
 ****************************************************************/
char *pr_strcat_cd(phiros_shell *dsh, char *msg, char *e, char *v_s)
{
char *bad_flag;

pr_strcpy(e, dsh->av[0]);
pr_strcat(e, ": ");
pr_strcat(e, v_s);
pr_strcat(e, ": ");
pr_strcat(e, dsh->args[0]);
pr_strcat(e, msg);
if (dsh->args[1][0] == '-')
{
bad_flag = malloc(3);
bad_flag[0] = '-';
bad_flag[1] = dsh->args[1][1];
bad_flag[2] = '\0';
pr_strcat(e, bad_flag);
free(bad_flag);
}
else
{
pr_strcat(e, dsh->args[1]);
}

pr_strcat(e, "\n");
pr_strcat(e, "\0");
return (e);
}
/**
 * e_g_cd - error message for cd command in get_cd
 * @dsh: data relevant (directory)
 * Return: Error message
 *****************************************************************/
char *e_g_cd(phiros_shell *dsh)
{
int lth, lth_id;
char *e, *v_s, *msg;

v_s = pr_itoa(dsh->counter);
if (dsh->args[1][0] == '-')
{
msg = ": Bad option ";
lth_id = 2;
}
else
{
msg = ": cannot cd to ";
lth_id = pr_strlen(dsh->args[1]);
}

lth = pr_strlen(dsh->av[0]) + pr_strlen(dsh->args[0]);
lth += pr_strlen(v_s) + pr_strlen(msg) + lth_id + 5;
e = malloc(sizeof(char) * (lth + 1));

if (e == 0)
{
free(v_s);
return (NULL);
}

e = pr_strcat_cd(dsh, msg, e, v_s);

free(v_s);

return (e);
}
/**
 * e_n_f - generic error message for command not found
 * @dsh: data relevant (counter, arguments)
 * Return: Error message
 */
char *e_n_f(phiros_shell *dsh)
{
int lth;
char *e;
char *v_s;

v_s = pr_itoa(dsh->counter);
lth = pr_strlen(dsh->av[0]) + pr_strlen(v_s);
lth += pr_strlen(dsh->args[0]) + 16;
e = malloc(sizeof(char) * (lth + 1));
if (e == 0)
{
free(e);
free(v_s);
return (NULL);
}
pr_strcpy(e, dsh->av[0]);
pr_strcat(e, ": ");
pr_strcat(e, v_s);
pr_strcat(e, ": ");
pr_strcat(e, dsh->args[0]);
pr_strcat(e, ": not found\n");
pr_strcat(e, "\0");
free(v_s);
return (e);
}
/**
 * e_e_s - generic error message for exit in get_exit
 * @dsh: data relevant (counter, arguments)
 * Return: Error message
 ***********************************************************/
char *e_e_s(phiros_shell *dsh)
{
int lth;
char *e;
char *v_s;

v_s = pr_itoa(dsh->counter);
lth = pr_strlen(dsh->av[0]) + pr_strlen(v_s);
lth += pr_strlen(dsh->args[0]) + pr_strlen(dsh->args[1]) + 23;
e = malloc(sizeof(char) * (lth + 1));
if (e == 0)
{
free(v_s);
return (NULL);
}
pr_strcpy(e, dsh->av[0]);
pr_strcat(e, ": ");
pr_strcat(e, v_s);
pr_strcat(e, ": ");
pr_strcat(e, dsh->args[0]);
pr_strcat(e, ": Bad number: ");
pr_strcat(e, dsh->args[1]);
pr_strcat(e, "\n\0");
free(v_s);

return (e);
}
