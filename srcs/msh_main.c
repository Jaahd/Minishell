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
		{
			tmp[i[2]++] = read_buff[i[0]];
		}
	}
	if (ft_strlen(tmp))
		ft_lstpushback(&arg, tmp);
	ret = lst_to_tbl(arg);
	return (ret);
}

char		*join_exe(char *s1, char *s2)
{
	if (DEBUG == 1)
		ft_putendl("join exe");
	char		*rlt;
	char		*tmp;

	tmp = ft_strjoin("/", s2);
	rlt = ft_strjoin(s1, tmp);
/*	ft_strdel(&s1);
	ft_strdel(&s2); */
	ft_strdel(&tmp);
	return (rlt);
}

int			fill_path(char ***env)
{
	if (DEBUG == 1)
		ft_putendl("fill path");
	char		*tmp;

	tmp = NULL;
	if (((*env) = (char **)malloc(sizeof(char *) * 3)) == NULL)
		return (-1);
	if ((tmp = getcwd(tmp, PATH_MAX)) == NULL)
		return (-1);
	(*env)[0] = "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin";
	(*env)[1] = ft_properjoin("PWD=", tmp);
	(*env)[2] = NULL;
	free(tmp);
	return (0);
}

int			check_fct(char **cmd, char **env, t_duo **env_cpy)
{
	if (DEBUG == 1)
		ft_putendl("check fct");
	char		**path;
	char		*tmp;
	int			i;

	(void)env;//  a virer
	tmp = get_env(env_cpy, "PATH");
	if(tmp == NULL)
		fill_path(&path);
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
	char		*builtin[] = {"cd", "setenv", "unsetenv", "env", "exit"};
	int			(*fct_tbl[])(char **cmd, t_duo **env)
		= {&bi_cd, &bi_setenv, &bi_unsetenv, &bi_env, &bi_exit};
	int			i;

	i = 0;
	while (i < 5 && ft_strcmp(cmd[0], builtin[i]) != 0)
		i++;
	if (i < 5 && ft_strcmp(cmd[0], builtin[i]) == 0)
	{
		if (fct_tbl[i](cmd, env) == -1)
			return (-1);
		else
			return (1);
	}
	return (0);
}

int			fct_read(char *read_buff, char **env, t_duo **env_cpy)
{
	if (DEBUG == 1)
		ft_putendl("read buff");
	int			ret;
	char		**cmd;
	t_duo		*env_cpy2;
	int			pouet;

	pouet = 0;
	env_cpy2 = *env_cpy;
	ret = 0;
	while ((ret = read(1, read_buff, BUFF_SIZE)) > 0)
	{
		cmd = read_n_check(SEP, read_buff);
/*	env_cpy2 = *env_cpy;
	ft_putendl("\navant");
	while (env_cpy2)
	{ft_putendl(env_cpy2->name); env_cpy2 = env_cpy2->next;
	}*/
		pouet = handle_builtin(cmd, env_cpy);
		if (pouet != 0)
			break ;
		father_n_son(cmd, env, env_cpy);
		break ;
	}
	return (0);
}

char		**cpy_env(char **env)
{
	char		**cpy;
	int			i;

	cpy = NULL;
	i = 0;
	if ((cpy = (char **)malloc(sizeof(char *) * tbl_len(env) + 1)))
	while (env[i])
	{
		cpy[i] = env[i];
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}

int			main(int ac, char **av, char **env)
{
	char		*read_buff;
	char		**cpy;
	t_duo		*env_cpy;

	(void)ac;
	(void)av;
	cpy = cpy_env(env);
	if (!(*env))
		fill_path(&cpy);
//	//a virer
//	int i =0;printf("debut liste\n");
//	while(cpy[i])
//	{printf("[%s]\n", cpy[i]), i++;}
//	printf("fin liste\n");
//	//jusque là
	env_cpy = tbl_to_duo(cpy, '=');
	read_buff = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	while (1)
	{
		ft_bzero(read_buff, BUFF_SIZE + 1);
		display_prompt(&env_cpy);
		fct_read(read_buff, cpy, &env_cpy);
	}
	return (0);
}
