#include "proshell.h"

/**
 * repeat_chars - counts the repetitions of a char
 * @input: input string
 * @z: index
 * Return: repetitions
 */
int repeat_chars(char *input, int z)
{
	if (*(input - 1) == *input)
		return (repeat_chars(input - 1, z + 1));

	return (z);
}
/**
 * cj_e_s_p - finds syntax errors
 * @input: input string
 * @z: index
 * @lt: last char read
 * Return: index of error. 0 when there are no errors
 */
int cj_e_s_p(char *input, int z, char lt)
{
	int c;

	c = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (cj_e_s_p(input + 1, z + 1, lt));

	if (*input == ';')
		if (lt == '|' || lt == '&' || lt == ';')
			return (z);

	if (*input == '|')
	{
		if (lt == ';' || lt == '&')
			return (z);

		if (lt == '|')
		{
			c = repeat_chars(input, 0);
			if (c == 0 || c > 1)
				return (z);
		}
	}

	if (*input == '&')
	{
		if (lt == ';' || lt == '|')
			return (z);

		if (lt == '&')
		{
			c = repeat_chars(input, 0);
			if (c == 0 || c > 1)
				return (z);
		}
	}

	return (cj_e_s_p(input + 1, z + 1, *input));
}

/**
 * cj_first_char - finds index of the first char
 * @input: input string
 * @z: index
 * Return: 1 if there is an error. 0 in other case.
 */
int cj_first_char(char *input, int *z)
{
	for (*z = 0; input[*z]; *z += 1)
	{
		if (input[*z] == ' ' || input[*z] == '\t')
			continue;

		if (input[*z] == ';' || input[*z] == '|' || input[*z] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * p_x_e - prints when a syntax error is found
 * @dtsh: data structure
 * @input: input string
 * @z: index of the error
 * @bool: to control msg error
 * Return: no return
 */
void p_x_e(project_shell *dtsh, char *input, int z, int bool)
{
	char *msg, *msg2, *msg3, *e, *counter;
	int length;

	if (input[z] == ';')
	{
		if (bool == 0)
			msg = (input[z + 1] == ';' ? ";;" : ";");
		else
			msg = (input[z - 1] == ';' ? ";;" : ";");
	}

	if (input[z] == '|')
		msg = (input[z + 1] == '|' ? "||" : "|");

	if (input[z] == '&')
		msg = (input[z + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = cj_itoa(dtsh->counter);
	length = cj_strlen(dtsh->av[0]) + cj_strlen(counter);
	length += cj_strlen(msg) + cj_strlen(msg2) + cj_strlen(msg3) + 2;

	e = malloc(sizeof(char) * (length + 1));
	if (e == 0)
	{
		free(counter);
		return;
	}
	cj_strcpy(e, dtsh->av[0]);
	cj_strcat(e, ": ");
	cj_strcat(e, counter);
	cj_strcat(e, msg2);
	cj_strcat(e, msg);
	cj_strcat(e, msg3);
	cj_strcat(e, "\0");

	write(STDERR_FILENO, e, length);
	free(e);
	free(counter);
}

/**
 * c_x_e - intermediate function to
 * find and print a syntax error
 * @dtsh: data structure
 * @input: input string
 * Return: 1 if there is an error, 0 otherwise
 */
int c_x_e(project_shell *dtsh, char *input)
{
	int b = 0;
	int f_c = 0;
	int q = 0;

	f_c = cj_first_char(input, &b);
	if (f_c == -1)
	{
		p_s_e(dtsh, input, b, 0);
		return (1);
	}

	q = cj_e_s_p(input + b, 0, *(input + b));
	if (q != 0)
	{
		p_s_e(dtsh, input, b + q, 1);
		return (1);
	}

	return (0);
}

