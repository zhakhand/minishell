
#include "../minishell.h"

int ft_env_no_args(t_data *data, t_cmd_node *node)
{
	int i;
//	int out_fd;

	i = 0;
	sort_env(data);
	// if (ft_strncmp(node->redirects->type, ">", 1) == 0)
	// {
	// 	out_fd = open(node->redirects->file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	// 	if (out_fd == -1)
	// 		panic("outfile");
	// 	if (dup2(out_fd, STDOUT_FILENO) == -1)
	// 		panic("dup2");
	// 	close(out_fd);
	// }
	// while (data->env[i] != NULL)
	// {
	// 	printf("%s\n", data->env[i]);
	// 	i++;
	// }
}

