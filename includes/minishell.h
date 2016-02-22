#ifndef MINISHELL_H
# define MINISHELL_H

# define DEBUG 0
# define SEP " \t\n\0"
# define BUFF_SIZE 1024

// pour ls a gerer : ~ ~+ ~- //
// builtin : cd setenv unsetenv env exit

/* pouet */
char		*get_env(char *to_find, char **env);
int			display_prompt(char **env);

/* builtin */
int			bi_env(char **arg, char ***env);
int			bi_exit(char **arg, char ***env);

#endif
