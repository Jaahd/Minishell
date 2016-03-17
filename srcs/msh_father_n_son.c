#include <unistd.h> // fork // execve // read // close
#include <stdlib.h> // exit // malloc // free
#include <fcntl.h> // open
#include <stdio.h>
#include <sys/wait.h> // wait
#include "minishell.h"
#include "libft.h"

static char		*join_exe(char *s1, char *s2)
{
	if (DEBUG == 1)
		ft_putendl("join exe");
	char		*rlt;
	char		*tmp;

	if (s2[0] == '/' || (s2[0] == '.' && s2[1] == '/'))
		return (s2);
	tmp = ft_strjoin("/", s2);
	rlt = ft_strjoin(s1, tmp);
/*	ft_strdel(&s1);
	ft_strdel(&s2); */
	ft_strdel(&tmp);
	return (rlt);
}

static int		check_fct(char **cmd, char **env, t_duo **env_cpy)
{
	if (DEBUG == 1)
		ft_putendl("check fct");
	char		**path;
	char		*tmp;
	int			i;

	tmp = get_env(env_cpy, "PATH");
	if (tmp == NULL)
		fill_path(&path);
	else
		path = read_n_check(":", tmp);
	i = 0;
	while (path[i])
	{
		tmp = join_exe(path[i], cmd[0]);
		execve(tmp, cmd, env);
		i++;
	}
	free(tmp);
	return (0);
}

int				father_n_son(char **cmd, char **env, t_duo **env_cpy)
{
	if (DEBUG == 1)
		ft_putendl("fatherandson");
	pid_t		father;
	int			stat_loc;

	father = fork();
	if (father > 0)
	{
		check_signal(3);
		wait(&stat_loc);
	}
	if (father == 0)
	{
		check_signal(2); // avec ctrl_c qui se comporte normalement
		check_fct(cmd, env, env_cpy);
		ft_putstr("minishell: ");
		ft_putstr(cmd[0]);
		ft_putendl(": command not found");
		exit(EXIT_FAILURE);
	}
	return (0);
}
