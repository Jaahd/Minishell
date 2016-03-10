#include <unistd.h> // fork // execve // read // close
#include <stdlib.h> // exit // malloc // free
#include <fcntl.h> // open 
#include <stdio.h>
#include <sys/wait.h> // wait
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
	/* a suppr----->
	i[0] = -1;
	ft_putendl("on commence la liste la :");
	while (ret[++i[0]])
		ft_putendl(ret[i[0]]);
	*/// <------ jusque la ;)
	return (ret);
}

char		*join_exe(char *s1, char *s2)
{
	char		*rlt;
	char		*tmp;

	tmp = ft_strjoin("/", s2);
	rlt = ft_strjoin(s1, tmp);
/*	ft_strdel(&s1);
	ft_strdel(&s2); */
	ft_strdel(&tmp);
	return (rlt);
}

char		**fill_path()
{
	char		**path;

	if ((path = (char **)malloc(sizeof(char *) * 6)) == NULL)
		return (NULL);
	path[0] = "/usr/local/bin";
	path[1] = "/usr/bin";
	path[2] = "/bin";
	path[3] = "/usr/sbin";
	path[4] = "/sbin";
	path[5] = NULL;
	return (path);
}

int			check_fct(char **cmd, char **env, t_duo **env_cpy)
{
	if (DEBUG == 1)
		ft_putendl("check fct");
	char		**path;
	char		*tmp;
	int			i;

	tmp = get_env(env_cpy, "PATH");
	if(tmp == NULL)
		 path = fill_path();
	else
		path = read_n_check(":", tmp);
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

int			father_n_son(char **cmd, char **env, t_duo **env_cpy)
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
		check_fct(cmd, env, env_cpy);
		exit(EXIT_FAILURE);
		//		ft_error(); //// TROUVER LE MESSAGE CORRESPONDANT + EXIT_FAILURE
	}
	return (0);
}

int			handle_builtin(char **cmd, t_duo **env)
{
	if (DEBUG == 1)
		ft_putendl("handle builtin");
	char		*builtin[] = {/*"cd", "setenv", "unsetenv",*/ "env", "exit"};
	int			(*fct_tbl[])(char **cmd, t_duo **env)
		//						= {bi_env};
		= {/*&bi_cd, &bi_setenv, &bi_unsetenv,*/ &bi_env, &bi_exit};
	int			i;

	i = 0;
	while (i < 5 && ft_strcmp(cmd[0], builtin[i]) != 0)
		i++;
	if (i < 5 && ft_strcmp(cmd[0], builtin[i]) == 0)
		if (fct_tbl[i](cmd, env) == -1)
			return (-1);
	return (0);
}

int			fct_read(char *read_buff, char **env, t_duo **env_cpy)
{
	if (DEBUG == 1)
		ft_putendl("read buff");
	int			ret;
	char		**cmd;

	ret = 0;
	while ((ret = read(1, read_buff, BUFF_SIZE)) > 0)
	{
		cmd = read_n_check(SEP, read_buff);
		if (handle_builtin(cmd, env_cpy) == -1)
			break ;
		father_n_son(cmd, env, env_cpy);
		break ;
	}
	return (0);
}
/*
t_duo		*cpy_env(char **env)
{
	if (DEBUG == 1)
		ft_putendl("cpy env");
	t_duo		*ret;
//	char		*tmp;
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (i = 0)
	{
		ret = (char **)malloc(sizeof(char *) * 2);
		ret[0] = ft_strjoin("PWD");
	}
	else
		ret = (char **)malloc(sizeof(char *) * (i + 1));
	while (env[i])
	{
		while (env[i][j])
		{
			if (env[i][j] == '=')
				ret->name = ft_strsub(env[i], 0, j);
			if (env[i][j] == '=' && env[i][j + 1])
				ret->value = ft_strsub(env[i], j + 1, ft_strlen(env[i]) - (j + 1));
			j++;
		}
		i++;
//		printf("name : %s\nvalue : %s\n\n", ret->name, ret->value);
		ret = ret->next;
	}
	return (ret);
}
*/
int			main(int ac, char **av, char **env)
{
	char		*read_buff;
	t_duo		*env_cpy;


	(void)ac;
	(void)av;
	env_cpy = tbl_to_duo(env, '=');
	read_buff = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	while (1)
	{
		ft_bzero(read_buff, BUFF_SIZE);
		display_prompt(env);
		fct_read(read_buff, env, &env_cpy);
	}
	return (0);
}
