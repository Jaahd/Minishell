#include <signal.h>
#include "minishell.h"
#include "libft.h"

static void		fct_m_ctrl_c(int sig)
{
	(void)sig;
	return ;
}

static void		fct_ctrl_c(int sig)
{
	(void)sig;
	return ;
}

static void		fct_ctrl_d(int sig)
{
	(void)sig;
	bi_exit(NULL, NULL);
}

int				check_signal(int loc)
{
	if (loc == 1)
		signal(SIGINT, fct_m_ctrl_c(SIGINT));
	else if (loc == 2)
		signal(SIGINT, fct_ctrl_c(SIGINT));
	signal(SIGQUIT, fct_ctrl_d(SIGQUIT));
	return (0);
}
