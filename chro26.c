#include "proshell.h"

/**
 * cj_without_comment - deletes comments from the input
 * @in: input string
 * Return: input without comments
 */
char *cj_without_comment(char *in)
{
	int z, z_to;

	z_to = 0;
	for (z = 0; in[z]; z++)
	{
		if (in[z] == '#')
		{
			if (z == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[z - 1] == ' ' || in[z - 1] == '\t' || in[z - 1] == ';')
				z_to = z;
		}
	}

	if (z_to != 0)
	{
		in = cj_realloc(in, z, z_to + 1);
		in[z_to] = '\0';
	}

	return (in);
}

/**
 * christy_s_loop - Loop of shell
 * @dtsh: data relevant (av, input, args)
 * Return: no return.
 */
void christy_s_loop(project_shell *dtsh)
{
	int loop, iff;
	char *input;

	for (loop = 1; loop == 1;)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = cj_read_line(&iff);
		if (iff != -1)
		{
			input = cj_without_comment(input);
			if (input == NULL)
				continue;

			if (c_x_e(dtsh, input) == 1)
			{
				dtsh->status = 2;
				free(input);
				continue;
			}
			input = rep_vari(input, dtsh);
			loop = cj_split_commands(dtsh, input);
			dtsh->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}
