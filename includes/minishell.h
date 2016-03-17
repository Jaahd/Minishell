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

t_duo		*savior(t_duo *env);

/* first_steps */
int			display_prompt(t_duo **env);
char		**cpy_env(char **env);
int			manage_tilde(t_duo **env, char **arg);
int			fill_path(char ***env);

/* signal */
int			check_signal(int loc);

/* builtin */
int			add_env(t_duo **env, char *name, char *value);
int			change_env(t_duo **env, char *name, char *value);
char		*get_env(t_duo **env, char *name);
int			handle_builtin(char **cmd, t_duo **env);

/* fct read */
char		**read_n_check(char *special, char *read_buff);
int			fct_read(char *read_buff, char **env, t_duo **env_cpy);

/* father_n_son */
int			father_n_son(char **cmd, char **env, t_duo **env_cpy);

/* env */
int			bi_env(char **arg, t_duo **env);

/* exit */
int			bi_exit(char **arg, t_duo **env);

/* setenv*/
int			bi_setenv(char **arg, t_duo **env);

/* unsetenv */
int			bi_unsetenv(char **arg, t_duo **env);

/* cd */
int			bi_cd(char **arg, t_duo **env);

#endif
