#ifndef _PHIROS_H_
#define _PHIROS_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* Points to an array of pointers to strings called the "environment" */
extern char **environ;


/**
 * struct phiros_shell - struct that contains all relevant data on runtime
 * @av: argument vector
 * @input: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
 */
typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} phiros_shell;

/**
 * struct sep_list_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} sep_list;

/**
 * struct line_list_s - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(phiros_shell *dsh);
} builtin_t;

/* phiros1.c */
char *pr_strcat_cd(phiros_shell *dsh, char *msg, char *e, char *v_s);
char *e_g_cd(phiros_shell *dsh);
char *e_n_f(phiros_shell *dsh);
char *e_e_s(phiros_shell *dsh);

/* phiros10.c */
char *pr_strdup(const char *s);
int pr_strlen(const char *s);
int compare_chars(char string[], const char *delim);
char *pr_strtok(char string[], const char *delim);
int pr_isdigit(const char *s);

/* phiros11.c */
void pr_rev_string(char *s);

/* phiros12.c */
void pr_cd_dot(phiros_shell *dsh);
void pr_cd_to(phiros_shell *dsh);
void pr_cd_previous(phiros_shell *dsh);
void pr_cd_to_home(phiros_shell *dsh);

/* phiros13.c */
int pr_cd_shell(phiros_shell *dsh);

/* phiros14.c */
int repeat_char(char *input, int u);
int pr_e_s_p(char *input, int u, char last);
int pr_first_char(char *input, int *u);
void p_s_e(phiros_shell *dsh, char *input, int u, int bool);
int c_s_e(phiros_shell *dsh, char *input);

/* phiros18.c */
int pr_exec_line(phiros_shell *dsh);

/* phiros19.c */
int pr_exit_shell(phiros_shell *dsh);

/* phiros20.c */
int (*pr_get_builtin(char *cmd))(phiros_shell *);

/* phiros21.c */
int pr_get_error(phiros_shell *dsh, int eva);

/* phiros22.c */
int pr_get_help(phiros_shell *dsh);

/* phiros23.c */
void pr_bring_line(char **lptr, size_t *i, char *buffer, size_t k);
ssize_t pr_get_line(char **lptr, size_t *i, FILE *stream);

/* phiros24.c */
void pr_get_sigint(int sig);
char *pr_read_line(int *iff);

/* phiros26.c */
char *pr_without_comment(char *in);
void s_loop(phiros_shell *dsh);

/* phiros27.c */
char *pr_swap_char(char *input, int bool);
void pr_add_nodes(sep_list **hs, line_list **hl, char *input);
void pr_go_next(sep_list **l_s, line_list **l_l, phiros_shell *dsh);
int pr_split_commands(phiros_shell *dsh, char *input);
char **pr_split_line(char *input);

/* phiros3.c */
void a_help_env(void);
void a_help_setenv(void);
void a_help_unsetenv(void);
void a_help_general(void);
void a_help_exit(void);

/* phiros4.c */
void a_help(void);
void a_help_alias(void);
void a_help_cd(void);

/* phiros5.c */
sep_list *pr_add_sep_node_end(sep_list **head, char sep);
void pr_free_sep_list(sep_list **head);
line_list *pr_add_line_node_end(line_list **head, char *line);
void pr_free_line_list(line_list **head);

/* phiros6.c */
r_var *pr_add_rvar_node(r_var **head, int lvar, char *val, int lval);
void pr_free_rvar_list(r_var **head);

/* phiros7.h */
void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *pr_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **pr_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);

/* phiros8.c */
int pr_get_len(int n);
char *pr_itoa(int n);
int pr_atoi(char *s);

/* phiros9.c */
char *pr_strcat(char *dest, const char *src);
char *pr_strcpy(char *dest, char *src);
int pr_strcmp(char *s1, char *s2);
char *pr_strchr(char *s, char c);
int pr_strspn(char *s, char *accept);

/* phiros25.c */
void pr_check_env(r_var **h, char *in, phiros_shell *data);
int pr_check_vars(r_var **h, char *in, char *st, phiros_shell *data);
char *replace_input(r_var **head, char *input, char *new_input, int nlen);
char *rep_variable(char *input, phiros_shell *dsh);

/* phiros17.c */
char *pr_copy_info(char *name, char *value);
void pr_set_env(char *name, char *value, phiros_shell *dsh);
int pr_setenv(phiros_shell *dsh);
int pr_unsetenv(phiros_shell *dsh);

/* phiros16.c */
int pr_cmp_env_name(const char *nenv, const char *name);
char *pr_getenv(const char *name, char **_environ);
int pr_env(phiros_shell *dsh);

/* phiros15.c */
int pr_is_cdir(char *path, int *m);
char *pr_which(char *cmd, char **_environ);
int pr_is_executable(phiros_shell *dsh);
int pr_check_error_cmd(char *d, phiros_shell *dsh);
int pr_cmd_exec(phiros_shell *dsh);

/* phiros2.c */
char *e_e(phiros_shell *dsh);
char *e_p_126(phiros_shell *dsh);


#endif
