#include "phiros.h"
/**
 * pr_check_env - checks if the typed variable is an env variable
 * @h: head of linked list
 * @in: input string
 * @data: data structure
 * Return: no return
 */
void pr_check_env(r_var **h, char *in, phiros_shell *data)
{
	int row, chr, k, lval;
	char **_envr;

	_envr = data->_environ;
	for (row = 0; _envr[row]; row++)
	{
		for (k = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = pr_strlen(_envr[row] + chr + 1);
				pr_add_rvar_node(h, k, _envr[row] + chr + 1, lval);
				return;
			}

			if (in[k] == _envr[row][chr])
				k++;
			else
				break;
		}
	}

	for (k = 0; in[k]; k++)
	{
		if (in[k] == ' ' || in[k] == '\t' || in[k] == ';' || in[k] == '\n')
			break;
	}

	pr_add_rvar_node(h, k, NULL, 0);
}
/**
 * pr_check_vars - check if the typed variable is $$ or $?
 * @h: head of the linked list
 * @in: input string
 * @st: last status of the Shell
 * @data: data structure
 * Return: no return
 */
int pr_check_vars(r_var **h, char *in, char *st, phiros_shell *data)
{
	int x, lst, lpd;

	lst = pr_strlen(st);
	lpd = pr_strlen(data->pid);

	for (x = 0; in[x]; x++)
	{
		if (in[x] == '$')
		{
			if (in[x + 1] == '?')
				pr_add_rvar_node(h, 2, st, lst), x++;
			else if (in[x + 1] == '$')
				pr_add_rvar_node(h, 2, data->pid, lpd), x++;
			else if (in[x + 1] == '\n')
				pr_add_rvar_node(h, 0, NULL, 0);
			else if (in[x + 1] == '\0')
				pr_add_rvar_node(h, 0, NULL, 0);
			else if (in[x + 1] == ' ')
				pr_add_rvar_node(h, 0, NULL, 0);
			else if (in[x + 1] == '\t')
				pr_add_rvar_node(h, 0, NULL, 0);
			else if (in[x + 1] == ';')
				pr_add_rvar_node(h, 0, NULL, 0);
			else
				pr_check_env(h, in + x, data);
		}
	}

	return (x);
}

/**
 * replace_input - replaces string into variables
 * @head: head of the linked list
 * @input: input string
 * @new_input: new input string (replaced)
 * @nlen: new length
 * Return: replaced string
 */
char *replace_input(r_var **head, char *input, char *new_input, int nlen)
{
	r_var *indx;
	int x, y, z;

	indx = *head;
	x = y = 0;
	while (y < nlen)
	{
		if (input[y] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new_input[x] = input[y];
				y++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (z = 0; z < indx->len_var; z++)
					y++;
				x--;
			}
			else
			{
				for (z = 0; z < indx->len_val; z++)
				{
					new_input[x] = indx->val[z];
					x++;
				}
				y += (indx->len_var);
				x--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[x] = input[y];
			y++;
		}
	}

	return (new_input);
}
/**
 * rep_variable - calls functions to replace string into vars
 * @input: input string
 * @dsh: data structure
 * Return: replaced string
 */
char *rep_variable(char *input, phiros_shell *dsh)
{
	r_var *head, *indx;
	char *status, *new_input;
	int olen, nlen;

	status = pr_itoa(dsh->status);
	head = NULL;

	olen = pr_check_vars(&head, input, status, dsh);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = replace_input(&head, input, new_input, nlen);

	free(input);
	free(status);
	pr_free_rvar_list(&head);

	return (new_input);
}
