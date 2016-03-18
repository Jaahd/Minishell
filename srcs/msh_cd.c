#include <unistd.h>
#include "minishell.h"
#include "libft.h"
//#include <sys/syslimits.h> // cf dans /usr/include/sys/syslimits.h ^^

static int		cd_usage(char **arg, char **path, char *tmp_old_pwd)
{
	if (DEBUG == 1)
		ft_putendl("cd usage");
	if (arg[2])
	{
		ft_putendl("cd: Too many arguments.");
		return (-1);
	}
	if (arg[1] && arg[1][0] == '-' && arg[1][1])
	{
		ft_putstr("minishell: cd: -");
		ft_putchar(arg[1][1]);
		ft_putendl(": invalide option\ncd: usage: cd [dir]");
		return (-1);
	}
	if (arg[1] && arg[1][0] == '-')
	{
		if (((*path) = ft_strdup(tmp_old_pwd)) == NULL)
		{
			ft_putendl("minishell: cd: variable $OLDPWD not set");
			return (-2);
		}
	}
	return (0);
}

static int		access_home(char **arg, char *home, char *tmp)
{
	ft_putstr("minishell: cd: ");
	if (home == NULL && !arg[1])
		ft_putendl("no $HOME variable set");
	else if (home == NULL && arg[1] && arg[1][0] == '~')
	{
		ft_putstr(tmp);
		ft_putendl(": no $HOME variable set");
	}
	return (-1);
}

static int		cd_access(char **arg, char *path, t_duo *env)
{
	if (DEBUG == 1)
		ft_putendl("cd access");
	char		*tmp;
	char		*home;

	tmp = NULL;
	home = get_env(&env, "HOME");
	if (path == NULL && arg[1] && arg[1][0] != '-')
		tmp = ft_strdup(arg[1]);
	if (path)
		tmp = ft_strdup(path);
	if (home == NULL && (!arg[1] || (arg[1] && arg[1][0] == '~')))
		return (access_home(arg, home, tmp));
	if (arg[1] && chdir(tmp) == -1)
	{
		ft_putstr("minishell: cd: ");
		ft_putstr(tmp);
		if ((access(tmp, F_OK)) == -1)
			ft_putendl(": no such file or directory");
		else
			ft_putendl(": permission denied");
		return (-1);
	}
	ft_strdel(&tmp);
	return (0);
}

static int		cd_home(t_duo **env, char ***arg)
{
	if (DEBUG == 1)
		ft_putendl("cd home");
	char		*home;

	free_tab(arg);
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

int				bi_cd(char **arg, t_duo **env)
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
	i = 0;
	path = NULL;
	i += cd_usage(arg, &path, tmp_old_pwd);
	if (i != -2)
		i += cd_access(arg, path, *env);
	if (i < 0)
		return (-1);
	ft_strdel(&path);
	if ((path = getcwd(path, MAX_PATH)) == NULL)
		return (-1);
	change_env(env, "OLDPWD", tmp_pwd);
	change_env(env, "PWD", path);
	return (0);
}
