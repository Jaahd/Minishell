#include <unistd.h>
//#include <sys/syslimits.h> // cf dans /usr/include/sys/syslimits.h ^^
#define PATH_MAX 1024
#include "minishell.h"
#include "libft.h"

int			cd_usage(char **arg, char **path)
{
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
			ft_putendl(": Permission denied");
		else
			ft_putendl(": No such file or directory");
		return (-1);
	}
	ft_strdel(&tmp);
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
	// var tmp pour sauvegarger le pwd actuel avant de verifier s'il faut effectivement le changer ou pas

	tmp_pwd = get_env(env, "PWD"); // strdup?
	tmp_old_pwd = get_env(env, "OLDPWD"); // strdup?
	i = 0;
	path = NULL;
	i += cd_usage(arg, &path);
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
