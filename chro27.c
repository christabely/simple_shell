#include "phiros.h"

/**
 * pr_swap_char - swaps | and & for non-printed chars
 * @input: input string
 * @bool: type of swap
 * Return: swapped string
 */
char *pr_swap_char(char *input, int bool)
{
int u;

if (bool == 0)
{
u = 0;
while (input[u])
{
if (input[u] == '|')
{
if (input[u + 1] != '|')
input[u] = 16;
else
u++;
}

if (input[u] == '&')
{
if (input[u + 1] != '&')
input[u] = 12;
else
u++;
}
u++;
}
}
else
{
u = 0;
while (input[u])
{
input[u] = (input[u] == 16 ? '|' : input[u]);
input[u] = (input[u] == 12 ? '&' : input[u]);
u++;
}
}
return (input);
}
/**
 * pr_add_nodes - add separators and command lines in the lists
 * @hs: head of separator list
 * @hl: head of command lines list
 * @input: input string
 * Return: no return
 */
void pr_add_nodes(sep_list **hs, line_list **hl, char *input)
{
	int u;
	char *line;

	input = pr_swap_char(input, 0);

	for (u = 0; input[u]; u++)
	{
		if (input[u] == ';')
			pr_add_sep_node_end(hs, input[u]);

		if (input[u] == '|' || input[u] == '&')
		{
			pr_add_sep_node_end(hs, input[u]);
			u++;
		}
	}

	line = pr_strtok(input, ";|&");
	do {
		line = pr_swap_char(line, 1);
		pr_add_line_node_end(hl, line);
		line = pr_strtok(NULL, ";|&");
	} while (line != NULL);

}
/**
 * pr_go_next - go to the next command line stored
 * @l_s: separator list
 * @l_l: command line list
 * @dsh: data structure
 * Return: no return
 */
void pr_go_next(sep_list **l_s, line_list **l_l, phiros_shell *dsh)
{
	int loop_sep;
	sep_list *ls_s;
	line_list *ls_l;

	loop_sep = 1;
	ls_s = *l_s;
	ls_l = *l_l;

	while (ls_s != NULL && loop_sep)
	{
		if (dsh->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*l_s = ls_s;
	*l_l = ls_l;
}

/**
 * pr_split_commands - splits command lines according to
 * the separators ;, | and &, and executes them
 * @dsh: data structure
 * @input: input string
 * Return: 0 to exit, 1 to continue
 */
int pr_split_commands(phiros_shell *dsh, char *input)
{

	sep_list *h_s, *l_s;
	line_list *h_l, *l_l;
	int loop;

	h_s = NULL;
	h_l = NULL;

	pr_add_nodes(&h_s, &h_l, input);

	l_s = h_s;
	l_l = h_l;

	while (l_l != NULL)
	{
		dsh->input = l_l->line;
		dsh->args = pr_split_line(dsh->input);
		loop = pr_exec_line(dsh);
		free(dsh->args);

		if (loop == 0)
			break;

		pr_go_next(&l_s, &l_l, dsh);

		if (l_l != NULL)
			l_l = l_l->next;
	}

	pr_free_sep_list(&h_s);
	pr_free_line_list(&h_l);

	if (loop == 0)
		return (0);
	return (1);
}
/**
 * pr_split_line - tokenizes the input string
 * @input: input string.
 * Return: string splitted.
 */
char **pr_split_line(char *input)
{
	size_t bs;
	size_t u;
	char **tokens;
	char *token;

	bs = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bs));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = pr_strtok(input, TOK_DELIM);
	tokens[0] = token;

	for (u = 1; token != NULL; u++)
	{
		if (u == bs)
		{
			bs += TOK_BUFSIZE;
			tokens = pr_reallocdp(tokens, u, sizeof(char *) * bs);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = pr_strtok(NULL, TOK_DELIM);
		tokens[u] = token;
	}

	return (tokens);
}
