
#include "../minishell.h"

int check_if_buildin(t_data *data, t_cmd_node *node)
{
//	printf("aaaaaaaa   %s\n", node->cmd_args[0]);
	printf("cmd_arg_0  %s\n", node->cmd_args[0]);
	if (node == NULL || node->cmd_args == NULL || node->cmd_args[0] == NULL)
		return (0);
	if (ft_strncmp(node->cmd_args[0], "cd", 2) == 0)
	{
		changedir(data, node);
		return (1);
	}
	if (ft_strncmp(node->cmd_args[0], "export", 7) == 0)
	{
		ft_export(data, node);
		return (1);
	}
	if (ft_strncmp(node->cmd_args[0], "pwd", 4) == 0)
	{
		show_pwd(data);
		return (1);
	}
	if (ft_strncmp(node->cmd_args[0], "unset", 5) == 0)
	{
		ft_unset(data, node);
		return (1);
	}
	if (ft_strncmp(node->cmd_args[0], "echo", 4) == 0)
	{
		ft_echo(node);
		return (1);
	}
	if (ft_strncmp(node->cmd_args[0], "env", 3) == 0)
	{
		ft_env_no_args(data, node);
		return (1);
	}
	else
		return (0);
}

