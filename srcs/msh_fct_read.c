#include <unistd.h> // fork // execve // read // close
#include <stdlib.h> // exit // malloc // free
#include "minishell.h"
#include "libft.h"

char		**read_n_check(char *special, char *read_buff)
{
	if (DEBUG == 1)
		ft_putendl("read n check");
	t_list		*arg;
	char		**ret;
	char		tmp[1024];
	int			i[] = {-1, 0, 0};

	ft_bzero(tmp, 1024);
	arg = NULL;
	while (read_buff[++i[0]])
	{
		i[1] = 0;
		while (read_buff[i[0]] != special[i[1]] && special[i[1]])
			i[1]++;
		if (read_buff[i[0]] == special[i[1]] && tmp[0] != '\0')
		{
			ft_lstpushback(&arg, tmp);
			ft_bzero(tmp, 1024);
			i[2] = 0;
		}
		else if (read_buff[i[0]] != special[i[1]])
			tmp[i[2]++] = read_buff[i[0]];
	}
	if (ft_strlen(tmp))
		ft_lstpushback(&arg, tmp);
	ret = lst_to_tbl(arg);
	return (ret);
}

int			fct_read(char *read_buff, char **env, t_duo **env_cpy)
{
	if (DEBUG == 1)
		ft_putendl("read buff");
	int			ret;
	char		**cmd;
	t_duo		*env_cpy2; // a virer
	int			i;

	i = 0;
	env_cpy2 = *env_cpy;
	ret = 0;
	while ((ret = read(1, read_buff, BUFF_SIZE)) > 0)
	{
		cmd = read_n_check(SEP, read_buff);
		while (cmd[i])
		{
			if (cmd[i][0] == '~')
				manage_tilde(env_cpy, &cmd[i]);
			i++;
		}
		i = 0;
/*	env_cpy2 = *env_cpy;
	ft_putendl("\navant");
	while (env_cpy2)
	{ft_putendl(env_cpy2->name); env_cpy2 = env_cpy2->next;
	}*/
		i = handle_builtin(cmd, env_cpy);
		if (i != 0)
			break ;
		father_n_son(cmd, env, env_cpy);
		break ;
	}
	if (ret == 0)
		bi_exit(NULL, env_cpy);
	return (0);
}
