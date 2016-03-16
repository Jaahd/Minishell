#ifndef MINISHELL_H
# define MINISHELL_H

# define DEBUG 0
# include <stdio.h>
#define PATH_MAX 1024 // a virer a 42 ;)

# define SEP " \t\n\0"
# define BUFF_SIZE 1024

# include "libft.h"
// pour ls a gerer : ~ ~+ ~- //
// builtin : cd setenv unsetenv env exit

/* pouet */
char		*get_env(t_duo **env, char *name);
int			display_prompt(t_duo **env);

/* builtin */
int			bi_env(char **arg, t_duo **env);

int			bi_exit(char **arg, t_duo **env);

int			bi_setenv(char **arg, t_duo **env);

int			bi_unsetenv(char **arg, t_duo **env);

int			bi_cd(char **arg, t_duo **env);

int			add_env(t_duo **env, char *name, char *value);
int			change_env(t_duo **env, char *name, char *value);
int			del_first(t_duo **env, char *name);
int			del_env(t_duo **env, char *name);
char		*get_env(t_duo **env, char *name);


#endif
