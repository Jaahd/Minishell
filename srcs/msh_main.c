#include <unistd.h> // fork // execve // read
#include <stdlib.h> // exit // malloc // free
#include <stdio.h>
#include <sys/wait.h> // wait
#include "minishell.h"
#include "libft.h"

int			read_n_check(char *read_buff, t_list **arg)
{
	if (DEBUG == 1)
		ft_putendl("read n check");
	char		tmp[1024];
	char		special[] = {" ;\n\0"};
	int			i[] = {0, 0, 0};

	ft_bzero(tmp, 1024);
	while (read_buff[i[0]])
	{
		i[1] = 0;
		while (read_buff[i[0]] != special[i[1]] && special[i[1]])
			i[1]++;
		if (read_buff[i[0]] == special[i[1]] && tmp[0] != '\0')
		{
			ft_lstpushback(arg, tmp);
			ft_bzero(tmp, 1024);
			i[2] = 0;
		}
		else if (read_buff[i[0]] != special[i[1]])
			tmp[i[2]++] = read_buff[i[0]];
		i[0]++;
	}
	if (ft_strlen(tmp))
		ft_lstpushback(arg, tmp);
	return (0);
}

char		*join_exe(char *s1, char *s2)
{
	char		*rlt;
	char		*tmp;

	tmp = ft_strjoin("/", s2);
	rlt = ft_strjoin(s1, tmp);
/*	ft_strdel(&s1);
	ft_strdel(&s2);
	ft_strdel(&tmp); */
	return (rlt);
}

int			check_fct(char **cmd, char **env)
{
	if (DEBUG == 1)
		ft_putendl("check fct");
	char		**path;
	char		*tmp;
	int			i;

	tmp = get_env("PATH", env);
	path = ft_strsplit(tmp, ':');
	i = 0;
	while(path[i])
	{
		tmp = join_exe(path[i], cmd[0]);
//		printf("cmd : %s\n", tmp);
		execve(tmp, cmd, env);
		i++;
	}
	free(tmp);
	return (0);
}

int			father_n_son(char **cmd, char **env)
{
	if (DEBUG == 1)
		ft_putendl("fatherandson");
	pid_t		father;
	int			stat_loc;

	father = fork();
	if (father > 0)
		wait(&stat_loc);
	if (father == 0)
	{
		check_fct(cmd, env);
		exit(EXIT_FAILURE);
//		ft_error(); //// TROUVER LE MESSAGE CORRESPONDANT + EXIT_FAILURE
	}
	return (0);
}

int			handle_builtin(char **cmd, char **env)
{
	if (DEBUG == 1)
		ft_putendl("handle builtin");
	char		*builtin[] = {"cd", "setenv", "unsetenv", "env", "exit"};
//	int			(*fct_tbl[])(char **cmd, char **env)
//						= {bi_env};
//						= {bi_cd, bi_setenv, bi_unsetenv, bi_env, bi_exit};
	int			i;

	i = 0;
	while (i < 5 && ft_strcmp(cmd[0], builtin[i]) != 0)
		i++;
	if (i < 5 && ft_strcmp(cmd[0], builtin[i]) == 0)
		bi_exit(cmd, env);
	return (0);
}

int			fct_read(char *read_buff, char **env)
{
	if (DEBUG == 1)
		ft_putendl("fct_read");
	int			ret;
	t_list		*arg;
	char		**cmd;

	ret = 0;
	arg = NULL;
	while ((ret = read(1, read_buff, BUFF_SIZE)) > 0)
	{
		read_n_check(read_buff, &arg);
		cmd = lst_to_tbl(arg);
		handle_builtin(cmd, env);
		father_n_son(cmd, env);
		break ;
	}
	return (0);
}

int			main(int ac, char **av, char **env)
{
	char		*read_buff;

	(void)ac;
	(void)av;
	read_buff = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	while (1)
	{
		ft_bzero(read_buff, BUFF_SIZE);
		display_prompt(env);
		fct_read(read_buff, env);
	}
	return (0);
}
