#ifndef MINISHELL_H
# define MINISHELL_H

# define DEBUG 0
# define SEP " \t\n\0"
# define BUFF_SIZE 1024

# include "libft.h"
// pour ls a gerer : ~ ~+ ~- //
// builtin : cd setenv unsetenv env exit

/* pouet */
char		*get_env(t_duo **env, char *name);
int			display_prompt(char **env);

/* builtin */
int			bi_env(char **arg, t_duo **env);
int			bi_exit(char **arg, t_duo **env);

#endif
