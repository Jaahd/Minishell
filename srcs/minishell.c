#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include "minishell.h"
#include "libft.h"

/// GETENV A CODER !!!!!!!!! //////


int			display_prompt()
{
	if (DEBUG == 1)
		ft_putendl("display prompt");
	char		*name;

	name = getenv("LOGNAME");
	if (name)
		ft_putstr(name);
	else
		ft_putchar('$');
	ft_putstr("> ");
	return (0);
}

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
	ft_strdel(&tmp);
*/	return (rlt);
}

int			check_fct(t_list *arg, char **env)
{
	if (DEBUG == 1)
		ft_putendl("check fct");
	char		**path;
	char		**cmd;
	char		*tmp;
	int			i;

	tmp = getenv("PATH");			// ma fct "getenv" remplacera
	path = ft_strsplit(tmp, ':');	// ces 2 lignes
//	free(tmp);
	cmd = lst_to_tbl(arg);
	i = 0;
	while(path[i])
	{
		tmp = join_exe(path[i], cmd[0]);
		printf("cmd : %s\n", tmp);
		execve(tmp, cmd, env);
		i++;
	}
	return (0);
}

int			father_n_son(char *read_buff, char **av, char **env)
{
	if (DEBUG == 1)
		ft_putendl("fatherandson");
	pid_t		father;
	t_list		*arg;
	int			stat_loc;

	(void)av;
	father = fork();
	arg = NULL;
	if (father > 0)
		wait(&stat_loc);
	if (father == 0)
	{
		read_n_check(read_buff, &arg);
/*		while (arg)
		{
			printf("[%s]\n", arg->content);
			arg = arg->next;
		}
*/		check_fct(arg, env);
		/*		if (ft_strcmp(read_buff, "ls\n") == 0)
				{
				printf("---%s\n", read_buff);
				execve("/bin/ls", av, env);
				}
				else
				{
				printf("toto\n");
				exit(EXIT_FAILURE);
				}
				*/	}
		return (0);
}

int			fct_read(char *read_buff, char **av, char **env)
{
	if (DEBUG == 1)
		ft_putendl("fct_read");
	int			ret;

	ret = 0;
	while ((ret = read(1, read_buff, BUFF_SIZE)) > 0)
	{
		father_n_son(read_buff, av, env);
		break ;
	}
	return (0);
}

int			main(int ac, char **av, char **env)
{
	char		*read_buff;

	(void)ac;
	read_buff = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	while (1)
	{
		ft_bzero(read_buff, BUFF_SIZE);
		display_prompt();
		fct_read(read_buff, av, env);
	}
	return (0);
}
