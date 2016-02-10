#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int			main(int ac, char **av, char **env)
{
	pid_t		father;
	int			stat_loc;

	(void)ac;
	father = fork();
	if (father > 0)
	{
		wait(&stat_loc);
		while (1)
		{
			printf("I am your father\n");
		}
	}
	if (father == 0)
	{
		execve("/bin/ls", av, env);
	}
}
