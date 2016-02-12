#ifndef MINISHELL_H
# define MINISHELL_H

# define DEBUG 0
# define BUFF_SIZE 1024

typedef struct		s_lst
{
	char			*name;
	struct list		*next;
}					t_lst;

#endif
