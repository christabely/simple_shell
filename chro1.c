#include "proshell.h"
/**
 * cj_strcat_cd - concatenates the msg for cd error
 * @dtsh: data relevant (directory)
 * @msg: message to print
 * @error: output message
 * @ver_s: counter lines
 * Return: error message
 **/
char *cj_strcat_cd(project_shell *dtsh, char *msg, char *error, char *ver_s)
{
    char *dangerous_flag;

    cj_strcpy(error, dtsh->av[0]);
    cj_strcat(error, ": ");
    cj_strcat(error, ver_s);
    cj_strcat(error, ": ");
    cj_strcat(error, dtsh->args[0]);
    cj_strcat(error, msg);
    if (dtsh->args[1][0] == '-')
    {
        dangerous_flag = malloc(3);
        dangerous_flag[0] = '-';
        dangerous_flag[1] = dtsh->args[1][1];
        dangerous_flag[2] = '\0';
        cj_strcat(error, dangerous_flag);
        free(dangerous_flag);
    }
    else
    {
        cj_strcat(error, dtsh->args[1]);
    }

    cj_strcat(error, "\n");
    cj_strcat(error, "\0");
    return (error);
}

/**
 * e_get_cd - error message for cd command in cj_get_cd
 * @dtsh: data relevant (directory)
 * Return: Error message
 **/
char *e_get_cd(project_shell *dtsh)
{
    int length, length_id;
    char *error, *ver_s, *msg;

    ver_s = cj_itoa(dtsh->counter);
    if (dtsh->args[1][0] == '-')
    {
        msg = ": Dangerous option ";
        length_id = 2;
    }
    else
    {
        msg = ": cannot cd to ";
        length_id = cj_strlen(dtsh->args[1]);
    }

    length = cj_strlen(dtsh->av[0]) + cj_strlen(dtsh->args[0]);
    length += cj_strlen(ver_s) + cj_strlen(msg) + length_id + 5;
    error = malloc(sizeof(char) * (length + 1));

    if (error == 0)
    {
        free(ver_s);
        return (NULL);
    }

    error = cj_strcat_cd(dtsh, msg, error, ver_s);

    free(ver_s);

    return (error);
}
/**
 * error_not_found - generic error message for command not found
 * @dtsh: data relevant (counter, arguments)
 * Return: Error message
 */
char *error_not_found(project_shell *dtsh)
{
    int length;
    char *error;
    char *ver_s;

    ver_s = cj_itoa(dtsh->counter);
    length = cj_strlen(dtsh->av[0]) + cj_strlen(ver_s);
    length += cj_strlen(dtsh->args[0]) + 16;
    error = malloc(sizeof(char) * (length + 1));
    if (error == 0)
    {
        free(error);
        free(ver_s);
        return (NULL);
    }
    cj_strcpy(error, dtsh->av[0]);
    cj_strcat(error, ": ");
    cj_strcat(error, ver_s);
    cj_strcat(error, ": ");
    cj_strcat(error, dtsh->args[0]);
    cj_strcat(error, ": not found\n");
    cj_strcat(error, "\0");
    free(ver_s);
    return (error);
}
/**
 * error_exit_s - generic error message for exit in get_exit
 * @dtsh: data relevant (counter, arguments)
 * Return: Error message
 **/
char *error_exit_s(project_shell *dtsh)
{
    int length;
    char *error;
    char *ver_s;

    ver_s = cj_itoa(dtsh->counter);
    length = cj_strlen(dtsh->av[0]) + cj_strlen(ver_s);
    length += cj_strlen(dtsh->args[0]) + cj_strlen(dtsh->args[1]) + 23;
    error = malloc(sizeof(char) * (length + 1));
    if (error == 0)
    {
        free(ver_s);
        return (NULL);
    }
    cj_strcpy(error, dtsh->av[0]);
    cj_strcat(error, ": ");
    cj_strcat(error, ver_s);
    cj_strcat(error, ": ");
    cj_strcat(error, dtsh->args[0]);
    cj_strcat(error, ": Dangerous number: ");
    cj_strcat(error, dtsh->args[1]);
    cj_strcat(error, "\n\0");
    free(ver_s);

    return (error);
}

