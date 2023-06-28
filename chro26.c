#include "phiros.h"

/**
 * pr_without_comment - deletes comments from the input
 * @in: input string
 * Return: input without comments
 */
char *pr_without_comment(char *in)
{
	int u, u_to;

	u_to = 0;
	for (u = 0; in[u]; u++)
	{
		if (in[u] == '#')
		{
			if (u == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[u - 1] == ' ' || in[u - 1] == '\t' || in[u - 1] == ';')
				u_to = u;
		}
	}

	if (u_to != 0)
	{
		in = pr_realloc(in, u, u_to + 1);
		in[u_to] = '\0';
	}

	return (in);
}

/**
 * s_loop - Loop of shell
 * @dsh: data relevant (av, input, args)
 * Return: no return.
 */
void s_loop(phiros_shell *dsh)
{
int loop, iff;
char *input;

for (loop = 1; loop == 1;)
{
write(STDIN_FILENO, "^-^ ", 4);
input = pr_read_line(&iff);
if (iff != -1)
{
input = pr_without_comment(input);
if (input == NULL)
continue;

if (c_s_e(dsh, input) == 1)
{
dsh->status = 2;
free(input);
continue;
}
input = rep_variable(input, dsh);
loop = pr_split_commands(dsh, input);
dsh->counter += 1;
free(input);
}
else
{
loop = 0;
free(input);
}
}
}
