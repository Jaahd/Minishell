#include <stdio.h>
#include "minishell.h"
#include "libft.h"
//#include <sys/syslimits.h> // cf dans /usr/include/sys/syslimits.h ^^

static char		*get_path(t_duo *env)
{
	if (DEBUG == 1)
		ft_putendl("get path");
	char			*path;
	char			*tmp;
	char			*home;

	home = get_env(&env, "HOME");
	path = get_env(&env, "PWD");
	tmp = ft_strsub(path, 0, ft_strlen(home));
	if (home && ft_strcmp(home, tmp) == 0)
	{
		free(tmp);
		tmp = ft_strsub(path, ft_strlen(home), ft_strlen(path));
		path = ft_properjoin("~", tmp);
	}
	free(home);
	free(tmp);
	return (path);
}

int				display_prompt(t_duo *env)
{
	if (DEBUG == 1)
		ft_putendl("display prompt");
	char			*name;
	char			*path;

	path = get_path(env);
	name = get_env(&env, "LOGNAME");
	if (name)
	{
		ft_putstr("\033[34;1m");
		ft_putstr(name);
		ft_putstr("\033[0m:");
	}
	if (path)
	{
		ft_putstr("\033[32;1m");
		ft_putstr(path);
		ft_putstr("\033[0m");
	}
	if (path || name)
		ft_putchar('\n');
	ft_putstr("\033[36m> \033[0m");
	return (0);
}

char			**cpy_env(char **env)
{
	if (DEBUG == 1)
		ft_putendl("cpy env");
	char			**cpy;
	int				i;

	cpy = NULL;
	i = 0;
	if ((cpy = (char **)malloc(sizeof(char *) * tbl_len(env) + 1)) == NULL)
	{
		printf("in cpy env");
		return (NULL);
	}
	while (env[i])
	{
		cpy[i] = env[i];
		i++;
	}
	cpy[i] = NULL;
	i = 0;
	while(cpy[i])
	{
	printf("**********[%s]***********\n", cpy[i]);
	i++;
	}
	return (cpy);
}

int				manage_tilde(t_duo **env, char **arg)
{
	if (DEBUG == 1)
		ft_putendl("manage tilde");
	char			*tmp;
	char			*home_path;

	tmp = ft_strsub(*arg, 1, ft_strlen(*arg));
	if ((home_path = get_env(env, "HOME")) == NULL)
		return (-1);
	free(*arg);
	if ((*arg = ft_properjoin(home_path, tmp)) == NULL)
		return (-1);
	return (0);
}

int				fill_path(char ***env)
{
	if (DEBUG == 1)
		ft_putendl("fill path");
	char			*tmp;

	tmp = NULL;
	if (((*env) = (char **)malloc(sizeof(char *) * 3)) == NULL)
		return (-1);
	if ((tmp = getcwd(tmp, MAX_PATH)) == NULL)
	{
		printf("-----------------trololo---------\n");
		return (-1);
	}
	(*env)[0] = "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin";
	(*env)[1] = ft_properjoin("PWD=", tmp);
	(*env)[2] = NULL;
	free(tmp);
	return (0);
}
