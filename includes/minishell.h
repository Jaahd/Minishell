#ifndef MINISHELL_H
# define MINISHELL_H

# define DEBUG 0
# define BUFF_SIZE 1024

// sur les mac : si env -i path ds etc/paths
// mais a priori pas sur linux....
// 
// builtin : cd setenv unsetenv env exit

/* pouet */
char		*get_env(char *to_find, char **env);
int			display_prompt(char **env);

/* builtin */
int			bi_env(char **arg, char **env);

#endif
