#include <stdio.h>
#include "minishell.h"
#include "libft.h"

int			display_prompt(t_duo **env)
{
	if (DEBUG == 1)
		ft_putendl("display prompt");
	char		*name;
	char		*path;
	int			i;

	i = 0;
	name = get_env(env, "LOGNAME");
	path = get_env(env, "PWD");
	if (name)
	{
		ft_putstr("\033[32;1m");
		ft_putstr(name);
		ft_putstr(": \033[0m");
	}
	if (path)
	{
		ft_putstr("\033[34;1m");
		ft_putstr(path);
		ft_putstr(" \033[0m");
	}
	ft_putstr("\033[36;1m$> \033[0m");
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

int			manage_tilde(t_duo **env, char **arg)
{
	if (DEBUG == 1)
		ft_putendl("manage tilde");
	int			i;
	char		*tmp;
	char		*home_path;

	i = 0;
	tmp = ft_strsub(*arg, 1, ft_strlen(*arg));
	if ((home_path = get_env(env, "HOME")) == NULL)
		return (-1);
	free(*arg);
	if ((*arg = ft_properjoin(home_path, tmp)) == NULL)
		return (-1);
	return (0);
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
