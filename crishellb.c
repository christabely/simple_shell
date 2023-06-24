#include "proshell.h"
/**
 * gleen - Get number lenght
 * @n: integer
 * Return: @n
 */
int gleen(int n)
{
	unsigned int gf;
	int lenght = 1;

	if (n < 0)
	{
		lenght++;
		gf = n * -1;
	}
	else
	{
		gf = n;
	}
	while (gf > 9)
	{
		lenght++;
		gf = n1 / 10;
	}
	return (lenght);
}
/**
 * aitoa - converts int to string
 * @n: integer
 * Return: string
 */
char *aitoa(int n)
{
	unsigned int gf;
	int lenght = gleen(n);
	char *b;

	b = malloc(sizeof(char) * (lenght + 1));
	if (b == 0)
		return (NULL);

	*(b + lenght) = '\0';

	if (n < 0)
	{
		gf = n * -1;
		b[0] = '-';
	}
	else
	{
		gf = n;
	}
	lenght--;
	do {
		*(b + lenght) = (gf % 10) + '0';
		gf = gf / 10;
		lenght--;
	}
	while (gf > 0)
		;
	return (b);
}
/**
 * atoii - to convert string to integer
 * @s: string
 * Return: number
 */
int atoii(char *s)
{
	unsigned int count = 0, size = 0, my = 0, up = 1, e = 1, j;

	while (*(s + count) != '\0')
	{
		if (size > 0 && (*(s + count) < '0' || *(s + count) > '9'))
			break;

		if (*(s + count) == '-')
			up *= -1;

		if ((*(s + count) >= '0') && (*(s + count) <= '9'))
		{
			if (size > 0)
				e *= 10;
			size++;
		}
		count++;
	}
	for (j = count - size; j < count; j++)
	{
		my = my + ((*(s + j) - 48) * e);
		e /= 10;
	}
	return (my * up);
}
