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

int				check_signal(int loc)
{
	if (loc == 1)
		signal(SIGINT, fct_m_ctrl_c);
	else if (loc == 2)
		signal(SIGINT, fct_ctrl_c);
	return (0);
}
