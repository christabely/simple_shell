#include "proshell.h"
/**
 * cj_rev_string - reverses a string.
 * @s: input string.
 * Return: no return.
 */
void cj_rev_string(char *s)
{
    int ct = 0, y, z;
    char *str, tmp;

    for (ct = 0; s[ct] != '\0'; ct++)
    {
        str = s;
    }

    y = 0;
    while (y < ct - 1)
    {
        z = y + 1;
        while (z > 0)
        {
            tmp = *(str + z);
            *(str + z) = *(str + (z - 1));
            *(str + (z - 1)) = tmp;
            z--;
        }
        y++;
    }
}

