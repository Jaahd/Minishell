#include <unistd.h>
//#include <sys/syslimits.h> // cf dans /usr/include/sys/syslimits.h ^^
#include "minishell.h"
#include "libft.h"

int			cd_usage(char **arg, char **path, char *tmp_old_pwd)
{
	if (DEBUG == 1)
		ft_putendl("cd usage");
	if (arg[2])
	{
		ft_putendl("cd: Too many arguments.");
		return (-1);
	}
	if (arg[1][0] == '-' && arg[1][1])
	{
		ft_putstr("minishell: cd: -");
		ft_putchar(arg[1][1]);
		ft_putendl(": invalide option\ncd: usage: cd [dir]");
		return (-1);
	}
	if (arg[1][0] == '-')
	{
		if (((*path) = ft_strdup(tmp_old_pwd)) == NULL)
		{
			ft_putendl("minishell: cd: OLDPWD not set");
			return (-1);
		}
	}
	return (0);
}

int			cd_access(char **arg, char *path)
{
	if (DEBUG == 1)
		ft_putendl("cd access");
	int			i;
	char		*tmp;

	if (path == NULL && arg[1][0] != '-')
		tmp = ft_strdup(arg[1]);
	if (path)
		tmp = ft_strdup(path);
	i = 0;
	if (chdir(tmp) == -1)
	{
		ft_putstr("minishell: cd: ");
		ft_putstr(tmp);
		if ((access(tmp, F_OK)) == -1)
			ft_putendl(": No such file or directory");
		else
			ft_putendl(": Permission denied");
		return (-1);
	}
	ft_strdel(&tmp);
	return (0);
}

int			manage_tilde(t_duo **env, char **arg)
{
	if (DEBUG == 1)
		ft_putendl("manage tilde");
	int			i;
	char		*tmp;
	char		*home_path;

	i = 0;
	if ((tmp = ft_strsub(*arg, 1, ft_strlen(*arg) - 1)) == NULL)
		return (-1);
	if ((home_path = get_env(env, "HOME")) == NULL)
		return (-1);
	free(*arg);
	if ((*arg = ft_properjoin(home_path, tmp)) == NULL)
		return (-1);
	return (0);
}

int			cd_home(t_duo **env, char ***arg)
{
	if (DEBUG == 1)
		ft_putendl("cd home");
	char		*home;

	free_tab(arg);
	printf("toto\n");
	if ((*arg = (char **)malloc(sizeof(char *) * 3)) == NULL)
		return (-1);
	if ((home = get_env(env, "HOME")) == NULL)
		return (-1);
	if (((*arg)[0] = ft_strdup("cd")) == NULL
			|| ((*arg)[1] = ft_strdup(home)) == NULL)
		return (-1);
	(*arg)[2] = NULL;
	return (0);
}

int			bi_cd(char **arg, t_duo **env)
{
	if (DEBUG == 1)
		ft_putendl("bi cd");
	char		*tmp_pwd;
	char		*tmp_old_pwd;
	char		*path;
	int			i;

	if ((tmp_pwd = get_env(env, "PWD")) == NULL)
		return (-1);
	tmp_old_pwd = get_env(env, "OLDPWD");
	if (!arg[1])
		cd_home(env, &arg);
	if (arg[1][0] == '~')
		manage_tilde(env, &arg[1]);
	i = 0;
	path = NULL;
	i += cd_usage(arg, &path, tmp_old_pwd);
	i += cd_access(arg, path);
	if (i < 0)
		return (-1);
	ft_strdel(&path);
	if ((path = getcwd(path, PATH_MAX)) == NULL) // a check ac David ....
		return (-1);
	change_env(env, "OLDPWD", tmp_pwd);
	change_env(env, "PWD", path);
	return (0);
}
