#include <unistd.h> // fork // execve // read // close
#include <stdlib.h> // exit // malloc // free
#include <fcntl.h> // open 
#include <stdio.h>
#include <sys/wait.h> // wait
#include "minishell.h"
#include "libft.h"

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
	read_buff = ft_strnew(BUFF_SIZE);
	while (1)
	{
		ft_bzero(read_buff, BUFF_SIZE + 1);
		check_signal(1); // avec ctrl-c ne fait rien
		display_prompt(&env_cpy);
		if (fct_read(read_buff, cpy, &env_cpy) < 0)
			ft_putendl(""); // pr le ctrl D verifier la valeur de ret quand on fait ctrl D et gerer avec ca ;)
	}
	return (0);
}
