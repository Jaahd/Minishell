#include "minishell.h"
#include "libft.h"
/*
char		*get_env(char *to_find, char **env)
{
	if (DEBUG == 1)
		ft_putendl("get env");
	int			i;
	int			size;
	int			size_env;

	i = 0;
	while(env[i])
	{
		size = ft_strlen(to_find);
		if (ft_strncmp(to_find, env[i], size) == 0)
		{
			size += 1;
			size_env = ft_strlen(env[i]);
			return (ft_strsub(env[i], size, (size_env - size)));
		}
		i++;
	}
	return (NULL);
}
*/
int			display_prompt(char **env)
{
	if (DEBUG == 1)
		ft_putendl("display prompt");
	char		*name;

	name = get_env(&env, "LOGNAME");
	if (name)
		ft_putstr(name);
	else
		ft_putchar('$');
	ft_putstr("> ");
	return (0);
}

