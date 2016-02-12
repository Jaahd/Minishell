#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include "minishell.h"
#include "libft.h"

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
/*
int			read_n_check(char *read_buff, char **env)
{
	t_lst		*cmd;
	char		*tmp;
	char		special[] = {' ', ';', '\n', '\0'};
	int			i;
	int			j;
	int			k;

	i = 0;
	k = 0;
	ft_bzero(tmp, 1024);
	while (read_buff[i])
	{
		j = 0;
		while (j < 4)
		{
			if (read_buff[i] == special[j])
			{
				cmd->name = ft_strdup(tmp);
				free(tmp);
				break ;
			}
			j++;
		}
		tmp[k] = read_buff[i];
		i++;
	}
	return (0);
}
*/
int			father_n_son(char *read_buff, char **av, char **env)
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
//		read_n_check(read_buff, env);
		if (ft_strcmp(read_buff, "ls\n") == 0)
		{
			printf("---%s\n", read_buff);
			execve("/bin/ls", av, env);
		}
		else
		{
			printf("toto\n");
			exit(EXIT_FAILURE);
		}
	}
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
