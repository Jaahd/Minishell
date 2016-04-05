/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_fct_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/05 18:06:15 by avacher           #+#    #+#             */
/*   Updated: 2016/04/05 18:06:15 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> // fork // execve // read // close
#include <stdlib.h> // exit // malloc // free
#include "minishell.h"
#include "libft.h"

char		**read_n_check(char *special, char *read_buff)
{
	t_list			*arg;
	char			tmp[1024];
	char			**tbl;
	static int		i[] = {-1, 0, 0};

	ft_bzero(tmp, 1024);
	arg = NULL;
	i[0] = -1;
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
	tbl = lst_to_tbl(arg);
	free_lst(&arg);
	return (tbl);
}

int			check_home(char **cmd)
{
	int			i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '~')
		{
			ft_putstr("minishell: ");
			ft_putstr(cmd[0]);
			ft_putendl(": no $HOME variable set");
			return (-1);
		}
		i++;
	}
	return (0);
}

int			fct_read(char *read_buff, char **env, t_duo **env_cpy)
{
	int				ret;
	char			**cmd;
	int				i;

	i = 0;
	ret = 0;
	while ((ret = read(0, read_buff, BUFF_SIZE)) > 0)
	{
		if ((cmd = read_n_check(SEP, read_buff)) == NULL || cmd[0] == NULL)
			return (-1);
		while (cmd[++i])
			if (cmd[i][0] == '~')
				manage_tilde(env_cpy, &cmd[i]);
		if (handle_builtin(cmd, env_cpy) != 0)
			break ;
		if (check_home(cmd) < 0)
			break ;
		father_n_son(cmd, env, env_cpy);
		break ;
	}
	if (ret <= 0)
		bi_exit(NULL, env_cpy);
	free_tab(&cmd);
	return (0);
}
