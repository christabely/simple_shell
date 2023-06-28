#include "phiros.h"

/**
 * repeat_char - counts the repetitions of a char
 * @input: input string
 * @u: index
 * Return: repetitions
 */
int repeat_char(char *input, int u)
{
	if (*(input - 1) == *input)
		return (repeat_char(input - 1, u + 1));

	return (u);
}
/**
 * pr_e_s_p - finds syntax errors
 * @input: input string
 * @u: index
 * @last: last char read
 * Return: index of error. 0 when there are no
 * errors
 */
int pr_e_s_p(char *input, int u, char last)
{
	int c;

	c = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (pr_e_s_p(input + 1, u + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (u);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (u);

		if (last == '|')
		{
			c = repeat_char(input, 0);
			if (c == 0 || c > 1)
				return (u);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (u);

		if (last == '&')
		{
			c = repeat_char(input, 0);
			if (c == 0 || c > 1)
				return (u);
		}
	}

	return (pr_e_s_p(input + 1, u + 1, *input));
}
/**
 * pr_first_char - finds index of the first char
 * @input: input string
 * @u: index
 * Return: 1 if there is an error. 0 in other case.
 */
int pr_first_char(char *input, int *u)
{
	for (*u = 0; input[*u]; *u += 1)
	{
		if (input[*u] == ' ' || input[*u] == '\t')
			continue;

		if (input[*u] == ';' || input[*u] == '|' || input[*u] == '&')
			return (-1);

		break;
	}

	return (0);
}
/**
 * p_s_e - prints when a syntax error is found
 * @dsh: data structure
 * @input: input string
 * @u: index of the error
 * @bool: to control msg error
 * Return: no return
 */
void p_s_e(phiros_shell *dsh, char *input, int u, int bool)
{
	char *msg, *msg2, *msg3, *e, *counter;
	int lth;

	if (input[u] == ';')
	{
		if (bool == 0)
			msg = (input[u + 1] == ';' ? ";;" : ";");
		else
			msg = (input[u - 1] == ';' ? ";;" : ";");
	}

	if (input[u] == '|')
		msg = (input[u + 1] == '|' ? "||" : "|");

	if (input[u] == '&')
		msg = (input[u + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = pr_itoa(dsh->counter);
	lth = pr_strlen(dsh->av[0]) + pr_strlen(counter);
	lth += pr_strlen(msg) + pr_strlen(msg2) + pr_strlen(msg3) + 2;

	e = malloc(sizeof(char) * (lth + 1));
	if (e == 0)
	{
		free(counter);
		return;
	}
	pr_strcpy(e, dsh->av[0]);
	pr_strcat(e, ": ");
	pr_strcat(e, counter);
	pr_strcat(e, msg2);
	pr_strcat(e, msg);
	pr_strcat(e, msg3);
	pr_strcat(e, "\0");

	write(STDERR_FILENO, e, lth);
	free(e);
	free(counter);
}
/**
 * c_s_e - intermediate function to
 * find and print a syntax error
 * @dsh: data structure
 * @input: input string
 * Return: 1 if there is an error. 0 in other case
 */
int c_s_e(phiros_shell *dsh, char *input)
{
	int b = 0;
	int f_char = 0;
	int i = 0;

	f_char = pr_first_char(input, &b);
	if (f_char == -1)
	{
		p_s_e(dsh, input, b, 0);
		return (1);
	}

	i = pr_e_s_p(input + b, 0, *(input + b));
	if (i != 0)
	{
		p_s_e(dsh, input, b + i, 1);
		return (1);
	}

	return (0);
}
