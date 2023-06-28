#include "phiros.h"
/**
 * pr_rev_string - reverses a string.
 * @s: input string.
 * Return: no return.
 */
void pr_rev_string(char *s)
{
int count = 0, m, n;
char *string, temp;

for (count = 0; s[count] != '\0'; count++)
{
string = s;
}

m = 0;
while (m < count - 1)
{
n = m + 1;
while (n > 0)
{
temp = *(string + n);
*(string + n) = *(string + (n - 1));
*(string + (n - 1)) = temp;
n--;
}
m++;
}
}
