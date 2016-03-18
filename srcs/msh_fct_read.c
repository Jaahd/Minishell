#include <unistd.h> // fork // execve // read // close
#include <stdlib.h> // exit // malloc // free
#include "minishell.h"
#include "libft.h"

char		**read_n_check(char *special, char *read_buff)
{
	if (DEBUG == 1)
		ft_putendl("read n check");
	t_list			*arg;
	char			**ret;
	char			tmp[1024];
	static int		i[] = {-1, 0, 0};

	printf("cette line : {{%s}} a diviser avec ca [[%s]]\n", read_buff, special);
	ft_bzero(tmp, 1024);
	arg = NULL;
	while (read_buff[++i[0]])
	{
		printf("*******(%c)*******\n", read_buff[i[0]]);
		i[1] = 0;
		while (read_buff[i[0]] != special[i[1]] && special[i[1]])
		{
		printf("dans le while\n");
			i[1]++;
		}
		if (read_buff[i[0]] == special[i[1]] && tmp[0] != '\0')
		{
		printf("dans le if\n");
			ft_lstpushback(&arg, tmp);
			ft_bzero(tmp, 1024);
			i[2] = 0;
		}
		else if (read_buff[i[0]] != special[i[1]])
		{
		printf("dans le else if\n");
			tmp[i[2]++] = read_buff[i[0]];
		}
	}
	if (ft_strlen(tmp))
		ft_lstpushback(&arg, tmp);
	t_list *temp;
	temp = arg;
	while(temp)
	{
	printf(">>>>>>>>>(%s)<<<<<<<<<<<<\n", temp->content);
	temp =temp->next;
	}
	ret = lst_to_tbl(arg);
	return (ret);
}

int			fct_read(char *read_buff, char **env, t_duo **env_cpy)
{
	if (DEBUG == 1)
		ft_putendl("read buff");
	int				ret;
	char			**cmd;
	int				i;

	i = -1;
	ret = 0;
	while ((ret = read(0, read_buff, BUFF_SIZE)) > 0)
	{
		if ((cmd = read_n_check(SEP, read_buff)) == NULL || cmd[0] == NULL)
			return (-1);
		while (cmd[++i])
		{
			if (cmd[i][0] == '~')
				manage_tilde(env_cpy, &cmd[i]);
		}
		i = 0;
		i = handle_builtin(cmd, env_cpy);
		if (i != 0)
			break ;
		father_n_son(cmd, env, env_cpy);
		break ;
	}
	if (ret <= 0)
		bi_exit(NULL, env_cpy);
	return (0);
}
